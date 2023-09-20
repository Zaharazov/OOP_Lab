#include <gtest/gtest.h> 
#include "func.hpp" 

TEST(test1, basic_test_set1) 
{ 
    ASSERT_TRUE(func("000")==0); 
} 

TEST(test2, basic_test_set2) 
{ 
    ASSERT_TRUE(func("10011")==7); 
} 

TEST(test3, basic_test_set3) 
{ 
    ASSERT_TRUE(func("1111111101")==511); 
} 

TEST(test4, basic_test_set4) 
{ 
    ASSERT_TRUE(func("0")==0); 
} 

TEST(test5, basic_test_set5) 
{ 
    ASSERT_TRUE(func("1")==1); 
} 

TEST(test6, basic_test_set6) 
{ 
    ASSERT_TRUE(func("0010111")==15); 
} 

TEST(test7, basic_test_set7)
{ 
    ASSERT_TRUE(func("11")==3); 
} 