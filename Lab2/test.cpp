#include <gtest/gtest.h>
#include "seven.hpp"

TEST(test1, basic_test_set1)
{
    Seven number1, number2;
    ASSERT_TRUE(number1.to_string() == '0' && num2.to_string() == '0');

    number1 = "23";
    number2 = "12";
    number2 = number2 + number1;

    EXPECT_FALSE(number1 == number2);
    EXPECT_FALSE(number1 > number2);
    EXPECT_TRUE(number1 < number2);
}

TEST(test2, basic_test_set2)
{
    Seven number1 {'2', '1', '2'};
    Seven number2 {'3', '4'};

    ASSERT_TRUE(number1.to_string() == "212" && number2.to_string() == "34");

    number1 = number1 - number2; // 212 - 34 = 145
    EXPECT_TRUE(number1.to_string() == "145");

    Seven number3 ('1', '0', '3');
    number3 = number3 + number2; // 103 + 34 = 140
    EXPECT_TRUE(number3.to_string() == "145");
}

TEST(test3, basic_test_set3)
{
    Seven number1 {'1', '0', '0'};
    Seven number2 {'1'};

    number1 = number1 - number2;
    EXPECT_TRUE(number3.to_string() == "66");

    number1 = "3";
    EXPECT_THROW(number2 - number1, std::underflow_error);
}
