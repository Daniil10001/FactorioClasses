#include"building.hpp"


Building::Building(unsigned id, point<ll> position):Object(id)
{
    set_cord(position.x,position.y);
    this->id=id;
}

Building::~Building()
{
    delete[] BuildingInventory;
    delete requirments; 
}

unsigned Building::get_material_quantity(unsigned id)
{
    for (unsigned i=0;i<requirments->count;i++)
        if(requirments->ids[i]==id)
            return BuildingInventory[i].get_quantity();
    return 0;
}