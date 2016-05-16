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
      difference_type pos_;
      
    public:
      iterator(node* curr_node, difference_type pos)
        : curr_node_{curr_node}
        , pos_{pos}
      {}
      
      iterator& operator++(void)
      {
        // if we're at the end of the vector...
        if (pos_ == node_size - 1) {
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
      
      reference operator*(void)
      {
        return curr_node_->vec[pos_];
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
            
    // Iterators
    iterator begin(void) const
    {
      return iterator{head_, 0};
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
      auto& vec = tail_->vec;
      vec.emplace_back(std::forward<Args>(args)...);
      ++size_;
    }
  };
}

#endif // REGULUS_UNROLLED_LIST_HPP_
