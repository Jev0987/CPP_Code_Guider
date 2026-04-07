/*
 * @Descripttion:
 * @Author: jev
 * @Date: 2026-03-28
 */
#include "calculator.h"
#include <gtest/gtest.h>

TEST(CalculatorTest, AddNum) {
    Calculator calc;

    EXPECT_EQ(calc.add(2, 3), 5);
    EXPECT_EQ(calc.add(10, 10), 20);
    EXPECT_EQ(calc.add(-1, 1), 0);
}

TEST(CalculatorTest, SubtractNums) {
    Calculator calc;

    ASSERT_EQ(calc.subtract(10, 10), 0);
    ASSERT_EQ(calc.subtract(10, 20), -10);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}