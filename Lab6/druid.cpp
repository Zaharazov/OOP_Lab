#include "druid.hpp"
#include "werewolf.hpp"
#include "squirrel.hpp"

Druid::Druid(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    status = true;
}

void Druid::print(std::ostream& out) 
{
    out << *this;
}

void Druid::accept(NPC* attacker, const int& distance) 
{
    if ((status && dynamic_cast<Squirrel*>(attacker)) || (status && dynamic_cast<Werewolf*>(attacker))) 
    {
        bool win = is_close(*attacker, distance);
        if (win) status = false;

        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Druid& other) 
{
    return out << "Druid " << other.name << " {" << other.x << ", " << other.y << '}';
}
