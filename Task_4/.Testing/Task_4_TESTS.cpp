#include <gtest/gtest.h>

#include "Task_4.h"

TEST(SumTest, From1to8) {
  ASSERT_EQ(findMaxSum(2,1), 9);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
