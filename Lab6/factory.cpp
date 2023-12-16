#include "factory.hpp"
#include "squirrel.hpp"
#include "werewolf.hpp"
#include "druid.hpp"

std::shared_ptr<NPC> factory(std::istream& in) 
{
    std::string type, name;
    size_t x, y;
    char c;
    in >> type >> name >> c >> x >> c >> y >> c;
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") 
    {
        res = std::make_shared<Squirrel>(x, y, name);
    }
    else if (type == "Druid") 
    {
        res = std::make_shared<Druid>(x, y, name);
    }
    else if (type == "Werewolf") 
    {
        res = std::make_shared<Werewolf>(x, y, name);
    }
    else if (type != "") 
    {
        std::cerr << "Unknown type" << std::endl;
    }
    return res;
}

std::shared_ptr<NPC> factory(const std::string& type, const std::string& name, const int& x, const int& y) 
{
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") 
    {
        res = std::make_shared<Squirrel>(x, y, name);
    }
    else if (type == "Druid") 
    {
        res = std::make_shared<Druid>(x, y, name);
    }
    else if (type == "Werewolf") 
    {
        res = std::make_shared<Werewolf>(x, y, name);
    }
    else 
    {
        std::cerr << "Unknown type" << std::endl;
    }
    return res;
}
