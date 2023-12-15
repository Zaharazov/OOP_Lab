#include <iostream>
#include <gtest/gtest.h>
#include "list.hpp"
#include "allocator.hpp"

TEST(test1, test_set1)
{
    List <int, Allocator<int>> l;
    EXPECT_EQ(l.size(), 0);
}

TEST(test2, test_set2)
{
    List <int, Allocator<int>> l(10, 1);
    EXPECT_EQ(l.size(), 10);
    for (int elem : l)
        EXPECT_EQ(elem, 1);
}

TEST(test3, test_set3)
{
    List <int, Allocator<int>> l(10);
    EXPECT_EQ(l.size(), 10);
    for (int elem : l)
        EXPECT_EQ(elem, 0);
}

TEST(test4, test_set4)
{
    List <int, Allocator<int>> l1 {1, 2, 3, 4, 5};
    EXPECT_EQ(l1.size(), 5);

    int i = 1;
    for (int elem : l1)
    {
        EXPECT_EQ(elem, i);
        i++;
    }

    List <int, Allocator<int>> l2 (l1);
    EXPECT_EQ(l2.size(), 5);

    int j = 1;
    for (int elem : l2)
    {
        EXPECT_EQ(elem, j);
        j++;
    }
}

TEST(test5, test_set5)
{
    List <int, Allocator<int>> l;
    l.push_back(2);
    EXPECT_EQ(l.size(), 1);
    for (int elem : l)
        EXPECT_EQ(elem, 2);
}

TEST(test6, test_set6)
{
    List <int, Allocator<int>> l;
    l.resize(3);
    EXPECT_EQ(l.size(), 3);
}
