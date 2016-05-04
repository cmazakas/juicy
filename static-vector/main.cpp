#include <cassert>
#include <algorithm>
#include <iostream>

#include "./include/static-vector.hpp"

int main(void)
{
  regulus::static_vector<int, 32> vec;
  
  assert(vec.size() == 0);
  
  for (int i = 0; i < 32; ++i) {
    vec.emplace_back(i);
  }

  for (int i = 0; i < 32; ++i) {
    assert(vec[i] == i);
  }
  
  assert(vec.size() == 32);
  
  std::for_each(
    vec.begin(), vec.end(),
    [](int& val)
    {
      val *= 2;
    });
  
  for (int i = 0; i < 32; ++i) {
    assert(vec[i] == (i * 2));
  }
  
  return 0;  
}
