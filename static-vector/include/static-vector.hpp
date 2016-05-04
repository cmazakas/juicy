#ifndef REGULUS_STATIC_VECTOR_HPP_
#define REGULUS_STATIC_VECTOR_HPP_

#include <cstddef>
#include <type_traits>
#include <stdexcept>
#include <iterator>

/**
  * This implementation is based off of the
  * example found at:
  * http://en.cppreference.com/w/cpp/types/aligned_storage
  */
namespace regulus
{
  template <typename T, std::size_t N>
  class static_vector
  {
  private:
      friend class iterator;
      
  public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;    
    
  private:
    std::aligned_storage_t<sizeof(T), alignof(T)> data_[N];
    size_type size_;
    
    pointer address_at(size_type const pos)
    {
      return reinterpret_cast<pointer>(data_ + pos);
    }
    
    const_pointer caddress_at(size_type const pos)
    {
      return reinterpret_cast<const_pointer>(data_ + pos);
    }
    
  public:
    class iterator
    {
    private:
      static_vector& vec_;
      difference_type pos_;
            
    public:
      iterator(static_vector& vec, difference_type const pos)
        : vec_{vec}
        , pos_{pos}
      {}
      
      bool operator==(iterator const& other)
      {
        return (pos_ == other.pos_);
      }
      
      bool operator!=(iterator const& other)
      {
        return !(*this == other);
      }
      
      reference operator*(void)
      {
        return *(vec_.address_at(pos_));
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
      
      iterator& operator+(size_type const pos)
      {
        pos_ += pos;
        return *this;
      }
    };
    
  public:
    // this constructor may be unnecessary if
    // size_type default-constructs to 0
    static_vector(void)
      : size_{0}
    {}
    
    ~static_vector(void)
    {
      for (size_type i = 0; i < size_; ++i) {
        caddress_at(i)->~value_type();
      }
    }
    
    template <typename ...Args>
    void emplace_back(Args&& ...args)
    {
      if (size_ >= N) {
        throw std::range_error{"Array size exceeded"};
      }
      
      new(address_at(size_)) value_type{std::forward<Args>(args)...};
      ++size_;
    }
    
    reference operator[](size_type const pos)
    {
      return *address_at(pos);
    }
        
    size_type size(void) const
    {
      return size_;
    }
    
    iterator begin(void)
    {
      return iterator{*this, 0};
    }
    
    iterator end(void)
    {
      return iterator{*this, (difference_type ) size_};
    }
  };
}

#endif // REGULUS_STATIC_VECTOR_HPP_