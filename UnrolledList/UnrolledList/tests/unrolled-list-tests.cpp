#include "./tests.hpp"

void unrolled_list_tests(void)
{
  describe("Regulus' unrolled list", []()
  {
    it("should be default constructible", []()
    {
      regulus::unrolled_list<int> list;
      
      assert(list.size() == 0);
      assert(list.capacity() == list.node_capacity);
    });
    
    it("should allow us to emplace_back() elements", []()
    {
      regulus::unrolled_list<int> list;
      
      int const val = 1337;
      list.emplace_back(val);
      
      assert(list.size() == 1);
      
      
      for (int i = 0; i < (int ) (list.capacity() - 1); ++i) {
        list.emplace_back(i);
      }
      
      assert(list.size() == list.capacity());
    });
  });
}