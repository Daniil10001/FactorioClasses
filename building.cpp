#include"building.hpp"


Building::Building(unsigned id, point<ll> position):Object(id)
{
    set_cord(position.x,position.y);
    this->id=id;
}

