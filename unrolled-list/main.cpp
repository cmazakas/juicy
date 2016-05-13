#include <cassert>
#include <iostream>

#include "include/unrolled-list.hpp"

using namespace regulus;

int main(void)
{
  // It should be default constructible
  {
    unrolled_list<int> list;
    assert(list.size() == 0);
  }
  
  // It should be emplace-able
  {
    int const val = 1337;
    unrolled_list<int> list;
    
    list.emplace_back(val);
    assert(list.size() == 1);
    
    list.emplace_back(val);
    assert(list.size() == 2);
  }
  
  // it should be iterable
  {
    unrolled_list<int> list;
    
    for (int i = 0; i < 32; ++i) {
      list.emplace_back(i);
    }
    
    assert(list.size() == 32);
    
    auto it = list.begin();
    for (int i = 0; i < 32; ++i, ++it) {
      assert(*it == i);
    }
  }
}
