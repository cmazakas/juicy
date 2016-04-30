#ifndef REGULUS_UNROLLED_LIST_HPP_
#define REGULUS_UNROLLED_LIST_HPP_

#include <cstddef>
#include <array>
#include <type_traits>
#include <utility>

namespace regulus
{
  template <typename T>
  class unrolled_list
  {
  public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef value_type& reference;
    typedef value_type&& rvalue_reference;
    typedef value_type* pointer;
    typedef pointer const const_pointer;
    
    size_type const static node_capacity = 32;
    
  private:
    struct node
    {
    public:
      node* next;
      node* prev;
      
    private:
      std::array<std::aligned_storage_t<sizeof(T), alignof(T)>, node_capacity> data_;
      size_type size_;
      
    public:
      node(void)
        : next{nullptr}
        , prev{nullptr}
        , size_{0}
      {}
      
      ~node(void)
      {
        auto data = data_.data();
        for (size_type i = 0; i < size_; ++i) {
          reinterpret_cast<const_pointer>(data + i)->~value_type();
        }
      }
      
      size_type size(void) const
      {
        return size_;
      }
      
      template <typename ...Args>
      void emplace_back(Args&& ...args)
      {
        new(data_.data() + size_) value_type{std::forward<Args>(args)...};
        ++size_;
      }
      
      reference operator[](size_type const idx) const
      {
        return *reinterpret_cast<pointer>(data_.data() + idx);
      }
      
      template <
        typename = std::enable_if_t<std::is_move_assignable<value_type>::value>>
      pointer insert_at(rvalue_reference rv, size_type const idx)
      {
        assert(size_ < node_capacity);
        
        auto data = data_.data();
        for (size_type i = (size_ - 1); i >= idx; --i) {
          auto to = *reinterpret_cast<pointer>(data + i + 1);
          auto from = *reinterpret_cast<pointer>(data + i);
          
          to = std::move(from);
        }
        
        new(data + idx) value_type{std::move(rv)};
        ++size_;
      }
    };
    
    class iterator
    {
      
    };
    
  private:
    node* head_;
    node* tail_;
    size_type size_;
    size_type capacity_;
    
  public:
    unrolled_list(void)
      : head_{new node}
      , tail_{head_}
      , size_{0}
      , capacity_{node_capacity}
    {
      
    }
    
    ~unrolled_list(void)
    {
      while (head_ != nullptr) {
        auto tmp = head_;
        head_ = head_->next;
        delete tmp;
      }
    }
    
    size_type size(void) const
    {
      return size_;
    }
    
    size_type capacity(void) const
    {
      return capacity_;
    }
    
    template <typename ...Args>
    void emplace_back(Args&&... args)
    {
      // for now, assume tail_->size < 32
      assert(tail_->size() < node_capacity);
      
      tail_->emplace_back(std::forward<Args>(args)...);
      ++size_;
    }
  };
}

#endif
