#include <sstream>
#include <vector>
#include <memory>
#include "squirrel.hpp"
#include "werewolf.hpp"
#include "druid.hpp"
#include "factory.hpp"
#include <gtest/gtest.h>

TEST(Constructors, Squirrel) 
{
    Squirrel s(0, 0, "Sandy");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Squirrel Sandy {0, 0}");
}

TEST(Constructors, Werewolf) 
{
    Werewolf w(1, 99, "Sumerok");
    std::stringstream out;
    w.print(out);
    ASSERT_EQ(out.str(), "Werewolf Sumerok {1, 99}");
}

TEST(Constructors, Druid) 
{
    Druid d(50, 50, "Woody");
    std::stringstream out;
    d.print(out);
    ASSERT_EQ(out.str(), "Druid Woody {50, 50}");
}
