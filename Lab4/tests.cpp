#include <gtest/gtest.h>
#include "triangle.hpp"
#include "square.hpp"
#include "octagon.hpp"

TEST(Group_1, basic_test_set) 
{
    Triangle <double> t(2);
    Square <double> s(2);
    Octagon <double> o(2);

    EXPECT_FALSE(t == s);
    EXPECT_FALSE(s == o);
    EXPECT_FALSE(t == o);

    EXPECT_TRUE(t == t);

    EXPECT_EQ(s.center(), std::make_pair(1.0, 1.0));
}

TEST(Group_2, basic_test_set) 
{
    Square <double> s(5);

    EXPECT_EQ((double)(s), 25);
    EXPECT_EQ(s.center(), std::make_pair(2.5, 2.5));
}

TEST(Group_3, basic_test_set) 
{
    Octagon <double> o1;
    Octagon <double> o2(4);
    EXPECT_FALSE(o1 == o2);
    o1 = o2;
    EXPECT_TRUE(o1 == o2);
}
