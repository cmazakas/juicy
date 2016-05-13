#ifndef REGULUS_UNROLLED_LIST_HPP_
#define REGULUS_UNROLLED_LIST_HPP_

#include "static-vector.hpp"

namespace regulus
{
  template <typename T>
  class unrolled_list
  {
  public:
    typedef T                 value_type;
    typedef std::size_t       size_type;
    typedef std::ptrdiff_t    difference_type;
    typedef value_type&       reference;
    typedef value_type const& const_reference;
    typedef size_type*        pointer;
    typedef size_type const*  const_pointer;
    
  private:
    std::size_t const static node_size = 32;
    struct node
    {
    public:
      static_vector<T, node_size> vec;
      node* next;
      node* prev;
      
    public:
      node(void)
        : next{nullptr}
        , prev{nullptr}
      {}
    };
    
  public:
    class iterator
    {
    private:
      node* curr_node_;
      typename static_vector<value_type, node_size>::iterator it_;
      
    public:
      iterator(node* curr_node, decltype(it_) it)
        : curr_node_{curr_node}
        , it_{it}
      {}
      
      iterator& operator++(void)
      {
        if (it_ == curr_node_->vec.end()) {
          curr_node_ = curr_node_->next;
          it_ = (curr_node_ != nullptr) ? curr_node_->vec.begin() : decltype(it_){};
        } else {
          ++it_;
        }
        
        return *this;
      }
      
      reference operator*(void)
      {
        return *it_;
      }
    };
    
  private:
    node *head_;
    node *tail_;
    size_type size_;
    
  public:
    unrolled_list(void)
      : head_{new node}
      , tail_{head_}
      , size_{0}
    {}
    
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
    
    template <typename ...Args>
    void emplace_back(Args&& ...args)
    {
      auto& vec = tail_->vec;
      vec.emplace_back(std::forward<Args>(args)...);
      ++size_;
    }
    
    iterator begin(void) const
    {
      return iterator{head_, head_->vec.begin()};
    }
  };
}

#endif // REGULUS_UNROLLED_LIST_HPP_
