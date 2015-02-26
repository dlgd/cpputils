#include <functional>
#include <iterator>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include "ut/algorithm.hpp"

template <typename T1, typename T2>
static std::pair<T1, T2> push_pair(const T1* v1, const T2* v2)
{
   return std::make_pair(v1 ? *v1 : 0, v2 ? *v2 : 0);
}

struct compare_pair_t
{
   template<typename T1, typename T2>
   bool operator()(const T1& lhs, const T2& rhs)
   {
      return lhs.first == rhs.first && lhs.second == lhs.second;
   }
};

TEST(zip_equal, empty)
{
   const std::vector<int> xs1;
   const std::vector<int> xs2;
   std::vector<std::pair<int, int>> output;

   ut::zip_equal(xs1.begin(), xs1.end(), xs2.begin(), xs2.end(),
                 std::back_inserter(output), push_pair<int, int>);

   EXPECT_TRUE(output.empty());
}

TEST(zip_equal, ints)
{
   const auto xs1 {2, 4, 6, 8};
   const auto xs2 {1, 2, 3, 4, 6};
   std::vector<std::pair<int, int>> output;

   ut::zip_equal(xs1.begin(), xs1.end(), xs2.begin(), xs2.end(),
                 std::back_inserter(output), push_pair<int, int>,
                 std::less<int>());

   const std::vector<std::pair<int, int>> expected_res =
      { {0, 1}, {2 ,2}, {0, 3}, {4 ,4}, {6, 6}, {8, 0} };

   ASSERT_EQ(expected_res.size(), output.size());

   EXPECT_TRUE(std::equal(output.begin(), output.end(),
                          expected_res.begin(), compare_pair_t()));
}

