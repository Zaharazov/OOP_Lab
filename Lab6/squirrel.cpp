#include "druid.hpp"
#include "werewolf.hpp"
#include "squirrel.hpp"

Squirrel::Squirrel(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    status = true;
}

void Squirrel::print(std::ostream& out) 
{
    out << *this;
}

 void Squirrel::accept(NPC* attacker, const int& distance) {}

std::ostream& operator<<(std::ostream& out, const Squirrel& other) 
{
    return out << "Squirrel " << other.name << " {" << other.x << ", " << other.y << '}';
}
