#ifndef REGULUS_STATIC_VECTOR_HPP_
#define REGULUS_STATIC_VECTOR_HPP_

#include <cstddef>
#include <type_traits>
#include <stdexcept>
#include <iterator>
#include <algorithm>

/**
  * This implementation is based off of the
  * example found at:
  * http://en.cppreference.com/w/cpp/types/aligned_storage
  */
namespace regulus
{
  template <
    typename T,
    std::size_t N,
    typename = std::enable_if_t<std::is_move_constructible<T>::value>
  >
  class static_vector
  {
  private:
      friend class iterator;
      
  public:
    // Member Types
    typedef T                 value_type;
    typedef std::size_t       size_type;
    typedef std::ptrdiff_t    difference_type;
    typedef value_type&       reference;
    typedef value_type const& const_reference;
    typedef value_type*       pointer;
    typedef value_type const* const_pointer;    
    
  private:
    // We use an array of POD types suitable for storing T
    std::aligned_storage_t<sizeof(T), alignof(T)> data_[N];
    size_type                                     size_;
    
    // 2 small helper functions for reading out of the array
    inline pointer address_at(size_type const pos)
    {
      return reinterpret_cast<pointer>(data_ + pos);
    }
    
    inline const_pointer caddress_at(size_type const pos) const
    {
      return reinterpret_cast<const_pointer>(data_ + pos);
    }
    
  public:
    class iterator :
      public std::iterator<std::random_access_iterator_tag, value_type>
    {
    private:
      friend class static_vector;
      
      static_vector& vec_;
      difference_type pos_;
            
    public:
      iterator(static_vector& vec, difference_type const pos)
        : vec_{vec}
        , pos_{pos}
      {}
      
      bool operator==(iterator const& other) const
      {
        return (pos_ == other.pos_);
      }
      
      bool operator!=(iterator const& other) const
      {
        return !(*this == other);
      }
      
      reference operator*(void)
      {
        return *(vec_.address_at(pos_));
      }
      
      pointer operator->(void)
      {
        return vec_.address_at(pos_);
      }
      
      iterator& operator++(void)
      {
        ++pos_;
        return *this;
      }
      
      iterator& operator++(int)
      {
        auto tmp = *this;
        ++(*this);
        return tmp;
      }
      
      iterator& operator--(void)
      {
        --pos_;
        return *this;
      }
      
      iterator& operator--(int)
      {
        auto tmp = *this;
        --(*this);
        return tmp;
      }
      
      iterator& operator+(difference_type const pos)
      {
        pos_ += pos;
        return *this;
      }
      
      iterator& operator-(difference_type const pos)
      {
        pos_ -= pos;
        return *this;
      }
      
      difference_type operator-(iterator other)
      {
        return pos_ - other.pos_;
      }
    };
    
  public:
    // this constructor may be unnecessary if
    // size_type default-constructs to 0
    static_vector(void)
      : size_{0}
    {}
    
    static_vector(const_reference init)
    {
      for (decltype(N) i = 0; i < N; ++i) {
        new(address_at(i)) value_type{init};
      }
      size_ = N;
    }
    
    ~static_vector(void)
    {
      for (size_type i = 0; i < size_; ++i) {
        caddress_at(i)->~value_type();
      }
    }
    
    // Element Access
    reference at(size_type const pos)
    {
      if (pos >= size_) {
        throw std::out_of_range{"Index is out of bounds!"};
      }
      return this->operator[](pos);
    }
        
    const_reference at(size_type const pos) const
    {
      if (pos >= size_) {
        throw std::out_of_range{"Index is out of bounds!"};
      }
      return this->operator[](pos);
    }
    
    reference operator[](size_type const pos)
    {
      return *address_at(pos);
    }
     
    const_reference operator[](size_type const pos) const
    {
      return *caddress_at(pos);
    }
    
    reference front(void)
    {
      return this->operator[](0);
    }
    
    const_reference front(void) const
    {
      return this->operator[](0);
    }
    
    reference back(void)
    {
      return this->operator[](size_ - 1);
    }
    
    const_reference back(void) const
    {
      return this->operator[](size_ - 1);
    }
    
    // Iterators
    iterator begin(void)
    {
      return iterator{*this, 0};
    }
    
    iterator end(void)
    {
      return iterator{*this, (difference_type ) size_};
    }
    
    // Capacity
    size_type size(void) const
    {
      return size_;
    }
    
    size_type capacity(void) const
    {
      return N;
    }
    
    // Modifiers
    iterator insert(iterator it, const_reference val)
    {
      auto pos = it.pos_;
      // move all elements to the right by 1
      for (difference_type i = size_ - 1; i >= pos; --i) {
        new(address_at(i + 1)) value_type{std::move(*address_at(i))};
      }
      
      // construct element in-place
      new(address_at(pos)) value_type{val};
      ++size_;
      
      // return iterator to the new element
      return iterator{*this, pos};
    }
    
    iterator erase(iterator it)
    {
      auto pos = it.pos_;
      it->~value_type();  
      for (difference_type i = pos + 1; i < (difference_type ) size_; ++i) {
        new(address_at(i - 1)) value_type{std::move(*address_at(i))};
      }

      --size_;
      return iterator{*this, pos};
    }
    
    template <typename ...Args>
    void emplace_back(Args&& ...args)
    {
      new(address_at(size_)) value_type{std::forward<Args>(args)...};
      ++size_;
    }
    
    void pop_back(void)
    {
      caddress_at(size_ - 1)->~value_type();
      --size_;
    }
    
    void resize(size_type const count)
    {
      for (size_type i = size_; i < count; ++i) {
        this->emplace_back();        
      }
    }
    
    static_vector slice(size_type const pos)
    {
      static_vector dst;
      for (size_type i = pos; i < size_; ++i) {
        dst.emplace_back(std::move(*address_at(i)));
      }
      size_ = pos;
      return dst;
    }
  };
}

#endif // REGULUS_STATIC_VECTOR_HPP_