#include <gtest/gtest.h>
#include <memory>
#include "npc.hpp"
#include "druid.hpp"
#include "werewolf.hpp"
#include "squirrel.hpp"

TEST(test1, Druid_constructor)
{
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Druid>(x, y);
    EXPECT_EQ(DruidType,a->get_type());
}

TEST(test2, Werewolf_constructor)
{
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Werewolf>(x, y);
    EXPECT_EQ(WerewolfType,a->get_type());
}

TEST(test3, Squirrel_constructor)
{
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x, y);
    EXPECT_EQ(SquirrelType,a->get_type());
}
