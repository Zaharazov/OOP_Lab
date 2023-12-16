#include "druid.hpp"
#include "werewolf.hpp"
#include "squirrel.hpp"

Werewolf::Werewolf(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    status = true;
}

void Werewolf::print(std::ostream& out) 
{
    out << *this;
}

void Werewolf::accept(NPC* attacker, const int& distance) 
{
    if (status && dynamic_cast<Squirrel*>(attacker)) 
    {
        bool win = is_close(*attacker, distance);
        if (win) status = false;
        
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Werewolf& other) 
{
    return out << "Werewolf " << other.name << " {" << other.x << ", " << other.y << '}';
}
