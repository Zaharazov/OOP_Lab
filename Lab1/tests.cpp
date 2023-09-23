#include <gtest/gtest.h> 
#include "eliminate_unset_bits.hpp" 

TEST(test1, basic_test_set1) 
{ 
    ASSERT_TRUE(eliminate_unset_bits("000")==0); 
} 

TEST(test2, basic_test_set2) 
{ 
    ASSERT_TRUE(eliminate_unset_bits("10011")==7); 
} 

TEST(test3, basic_test_set3) 
{ 
    ASSERT_TRUE(eliminate_unset_bits("1111111101")==511); 
} 

TEST(test4, basic_test_set4) 
{ 
    ASSERT_TRUE(eliminate_unset_bits("0")==0); 
} 

TEST(test5, basic_test_set5) 
{ 
    ASSERT_TRUE(eliminate_unset_bits("1")==1); 
} 

TEST(test6, basic_test_set6) 
{ 
    ASSERT_TRUE(eliminate_unset_bits("0010111")==15); 
} 

TEST(test7, basic_test_set7)
{ 
    ASSERT_TRUE(eliminate_unset_bits("11")==3); 
} 
