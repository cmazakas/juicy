#include <cassert>
#include <iostream>
#include <ctime>
#include <list>

#include "include/unrolled-list.hpp"

using regulus::unrolled_list;

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
  
  // it be able to handle more elements than an individual
  // vector can
  {
    unrolled_list<int> list;
    auto const new_size = list.node_size * 2;
    for (int i = 0; i < (int ) new_size; ++i) {
      list.emplace_back(i);
    }
    
    assert(list.size() == new_size);
    
    {
      int i = 0;
      for (auto l : list) {
        assert(l == i);
        ++i;
      }
    }
  }
  
  // it should be bidirectionally iterable
  {
    unrolled_list<int> list;
    auto const new_size = list.node_size * 2;
    for (int i = 0; i < (int ) new_size; ++i) {
      list.emplace_back(i);
    }
    
    assert(list.size() == new_size);
    
    auto it = --list.end();
    
    int i = list.size() - 1;
    do {
      assert(*it == i);
      --it;
      --i;
    } while (it != list.begin());
  }
  
  // it should be distance-able
  {
    unrolled_list<int> list;
    auto const new_size = list.node_size * 2;
    for (int i = 0; i < (int ) new_size; ++i) {
      list.emplace_back(i);
    }
    
    assert(std::distance(list.begin(), list.end()) == new_size);
  }
  
  int num_elements = 1024 * 1024 * 2;
  
  double my_time = 0;
  double stl_time = 0;
  
  {
    auto begin = std::clock();
    regulus::unrolled_list<int> list;
    for (int i = 0; i < num_elements; ++i) {
      list.emplace_back(i);
    }
    
    auto it = list.begin();
    do {
      ++it;
    } while (it != list.end());
    
    auto end = std::clock();
    my_time = double{(double ) end - begin} / CLOCKS_PER_SEC;
  }
  
  {
    auto begin = std::clock();
    
    std::list<int> list_;
    for (int i = 0; i < num_elements; ++i) {
      list_.emplace_back(i);
    }
    
    auto it = list_.begin();
    do {
      ++it;
    } while (it != list_.end());
    
    auto end = std::clock();
    stl_time = double{(double ) end - begin} / CLOCKS_PER_SEC;
  }
  
  std::cout << "My time : " << my_time << std::endl;
  std::cout << "STL time : " << stl_time << std::endl;
}
