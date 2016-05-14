#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstring>

#include "./include/static-vector.hpp"

int main(void)
{
  // it should be default constructible
  {
    regulus::static_vector<int, 32> vec;
    assert(vec.size() == 0);    
  }
  
  // we should be able to emplace_back elements...
  {
    regulus::static_vector<int, 32> vec;
    for (int i = 0; i < 32; ++i) {
      vec.emplace_back(i);
    }
    
    for (int i = 0; i < 32; ++i) {
      assert(vec[i] == i);
    }
    
    assert(vec.size() == 32);
  }
  
  // it should be STL-compliant and offer element access...
  {
    regulus::static_vector<int, 32> vec;
    for (int i = 0; i < 32; ++i) {
      vec.emplace_back(i);
    }
    
    std::for_each(
      vec.begin(), vec.end(),
      [](int& val)
      {
        val *= 2;
      });
    
    for (int i = 0; i < 32; ++i) {
      assert(vec[i] == (i * 2));
    }
  }

  // it should support try-catchable element access...
  {
    regulus::static_vector<int, 32> vec;
    vec.emplace_back(1337);
    
    assert(vec.size() == 1);
    
    try {
      int cpy = vec.at(vec.size() * 4); // oh no!!!
      assert(cpy == 1337);
    } catch(std::exception& e) {
      assert(std::strcmp(e.what(), "Index is out of bounds!") == 0);
    }
  }
  
  // it should support front/back access
  {
    regulus::static_vector<int, 32> vec;
    for (int i = 0; i < 32; ++i) {
      vec.emplace_back(i);
    }
    
    assert(vec.front() == 0);
    assert(vec.back() == 31);
  }

  
  // it should support some const stuff
  {
    regulus::static_vector<int, 32> vec;
    for (int i = 0; i < 32; ++i) {
      vec.emplace_back(i);
    }
    
    regulus::static_vector<int, 32> const& ref = vec;
    for (int i = 0; i < (int ) ref.size(); ++i) {
      assert(ref[i] == i);
    }
  }
  
  // we should be able to remove elements
  {
    regulus::static_vector<int, 32> vec;
    for (int i = 0; i < 32; ++i) {
      vec.emplace_back(i);
    }
    
    auto old_size = vec.size();
    for (int i = 0; i < 5; ++i) {
      vec.pop_back();
    }
    assert(vec.size() == old_size - 5);
  }
  
  // it should be insert-able
  {
    regulus::static_vector<int, 32> vec;
    for (int i = 0; i < 16; ++i) {
      vec.emplace_back(i);
    }
    
    auto test_it = vec.insert(vec.begin() + 8, 1337);
    assert(*test_it == 1337);
    assert(vec.size() == 17);
  }
        
  // it should be value constructible
  {
    int const init = 1337;
    regulus::static_vector<int, 32> vec{init};
    assert(vec.size() == 32);
    
    for (auto val : vec) {
      assert(val == init);
    }
  }
  
  // it should support slicing
  {
    int const init = 1337;
    std::size_t const N = 32;
    regulus::static_vector<int, N> vec{init};
    
    std::size_t slice_idx = 10;
    
    auto chunk = vec.slice(slice_idx);
    assert(chunk.size() == N - slice_idx);
    assert(vec.size() == slice_idx);
    
    for (auto i : vec) {
      assert(i == init);
    }
    
    for (auto i : chunk) {
      assert(i == init);
    }
  }
  
  // it should support non-trivial types
  {
    struct non_trivial
    {
      int* ptr;
      
      non_trivial(void)
        : ptr{new int{0}}
      {}
      
      // it's up to the implementation of non-trivial classes
      // to define the appropriate constructor overloads
      // for the vector to work properly
      non_trivial(non_trivial const& other)
      {
        ptr = new int;
        *ptr = *other.ptr;
      }
      
      ~non_trivial(void)
      {
        delete ptr;
      }
    };
    
    non_trivial init;
    std::size_t const N = 32;
    regulus::static_vector<non_trivial, N> vec{init};
    assert(vec.size() == N);
  }
  
  // it should be resize-able
  {
    std::size_t const size = 32;
    regulus::static_vector<int, size> vec;
    
    assert(vec.size() == 0);
    
    vec.resize(size);
    
    assert(vec.size() == size);
    assert(int{} == 0);
    for (auto v : vec) {
      assert(v == 0);
    }
  }
  
  // it should be transform-able
  {
    std::size_t const size = 32;
    regulus::static_vector<int, size> a;
    decltype(a) b;
    
    for (int i = 0; i < (int ) size; ++i) {
      a.emplace_back(i);
    }
    
    b.resize(size);
    
    assert(a.size() == size);
    assert(a.size() == b.size());
    
    std::transform(a.begin(), a.end(), b.begin(), [](int x)
    {
      return x * x;
    });
    
    for (int i = 0; i < (int ) size; ++i) {
      assert(b[i] == i * i);
    }
  }
  
  // it should support erasing
  {
    regulus::static_vector<int, 128> vec;
    for (int i = 0; i < 128; ++i) {
      vec.emplace_back(i);
    }
    
    assert(vec.size() == 128);
    assert(*(vec.begin() + 64) == 64);
    
    auto it = vec.erase(vec.begin() + 64);
    assert(*it == 65);
    assert(vec.size() == 127);
    
    for (auto i : vec) {
      assert(i != 64);
    }
  }
  
  // erasing an element at the end should return an
  // end-iterator
  {
    regulus::static_vector<int, 32> vec{1337};
    assert(vec.size() == 32);
    
    typename regulus::static_vector<int, 32>::iterator it = vec.end() - 1;
    
    assert(std::distance(vec.begin(), it) == 31);
    assert(*it == 1337);
    
    auto diff_it = vec.erase(it);
    assert(vec.size() == 31);
    assert(diff_it == vec.end());
  }
        
  return 0;  
}
