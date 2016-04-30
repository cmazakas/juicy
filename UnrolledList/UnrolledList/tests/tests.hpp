#ifndef REGULUS_UNROLLED_LIST_TESTS_HPP_
#define REGULUS_UNROLLED_LIST_TESTS_HPP_

#include <iostream>
#include <cassert>

#include "../include/unrolled-list.hpp"

/*  
  Helpers that we use to output test data
*/
template <typename F>
void describe(char const* msg, F f)
{
  std::cout << msg << std::endl;
  f();
  std::cout << "Tests passed!" << std::endl;
}

template <typename F>
void it(char const* msg, F f)
{
  std::cout << "\t" << msg << std::endl;
  f();
}

/*
  Test functions
*/  
void run_test_suite(void);
void unrolled_list_tests(void);

#endif // REGULUS_UNROLLED_LIST_TESTS_HPP_
