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
    
    std::size_t const static node_size = 32;
    
  private:
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
    class iterator :
      public std::iterator<std::bidirectional_iterator_tag, value_type>
    {
    private:
      node* curr_node_;
      difference_type pos_;
      
    public:
      iterator(node* curr_node, difference_type pos)
        : curr_node_{curr_node}
        , pos_{pos}
      {}
            
      reference operator*(void)
      {
        return curr_node_->vec[pos_];
      }
      
      bool operator==(iterator const& other)
      {
        return (curr_node_ == other.curr_node_ && pos_ == other.pos_);
      }
      
      bool operator!=(iterator const& other)
      {
        return !(*this == other);
      }
      
      iterator& operator++(void)
      {
        // if we're at the end of the vector...
        if (pos_ == (difference_type ) curr_node_->vec.size() - 1) {
          // find out if there's another node for us
          auto next = curr_node_->next;
          if (next != nullptr) {
            // we hop nodes of our list and reset the position
            // breaks program flow
            curr_node_ = next;
            pos_ = 0;
            return *this;
          }
        }
        
        // even if we're at the last element of the tail,
        // we still want to increment because we must still
        // return an iterator to match end()
        ++pos_;
        return *this;
      }
      
      iterator& operator--(void)
      {
        if (pos_ == 0) {
          auto prev = curr_node_->prev;
          if (prev != nullptr) {
            curr_node_ = prev;
            pos_ = curr_node_->vec.size() - 1;
            return *this;
          }
        }
        
        --pos_;
        return *this;
      }
    };
    
  private:
    node *head_;
    node *tail_;
    size_type size_;
    
  private:
    node* insert_node(node& curr)
    {
      auto next = curr.next;
      auto new_node = new node;
      
      curr.next = new_node;
      new_node->prev = std::addressof(curr);
      new_node->next = next;
      
      // in the case of the tail pointer, the next pointer
      // is null
      if (next) {
        next->prev = new_node;
      }
      
      return new_node;
    }
    
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
            
    // Iterators
    iterator begin(void) const
    {
      return iterator{head_, 0};
    }
    
    iterator end(void) const
    {
      return iterator{tail_, (difference_type ) tail_->vec.size()};
    }
    
    // Capacity
    size_type size(void) const
    {
      return size_;
    }
    
    // Modifiers
    template <typename ...Args>
    void emplace_back(Args&& ...args)
    {
      if (tail_->vec.size() == tail_->vec.capacity()) {
        auto old_tail = tail_;
        tail_ = insert_node(*old_tail);
        tail_->vec = std::move(old_tail->vec.slice(node_size / 2));
      }
      
      tail_->vec.emplace_back(std::forward<Args>(args)...);
      ++size_;
    }
  };
}

#endif // REGULUS_UNROLLED_LIST_HPP_
