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
  /*try {
    int cpy = vec.at(vec.size() * 4); // oh no!!!
    assert(cpy == 1337);
  } catch(std::exception& e) {
    assert(std::strcmp(e.what(), "Index is out of bounds!") == 0);
  }*/
  
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
    
    // it should support slicing
    {
      int const init = 1337;
      regulus::static_vector<int, 32> vec{init};
      
      auto chunk = vec.slice(32 - 10);
      assert(chunk.size() == 10);
      assert(vec.size() == 32 - 10);
    }
  }
        
  return 0;  
}
