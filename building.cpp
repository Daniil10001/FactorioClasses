#include"building.hpp"

unsigned min(unsigned a, unsigned b) {
    if (a > b) return b;
    return a;
}

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

unsigned Building::get_material_quantity(unsigned id) const
{
    for (unsigned i=0;i<requirments->count;i++)
        if(requirments->ids[i]==id)
            return BuildingInventory[i].get_quantity();
    return 0;
}

State Building::get_state() const
{
    return State::OK;
}

ActionResult Building::put_material(Material *m) {
    for (unsigned i = 0; i < requirments->count; i++) {
        if (requirments->ids[i] == m->getId()) {
            BuildingInventory[i] + *m;
            return ActionResult::OK;
        }
    }
    return ActionResult::BAD;
}

Material* Building::get_material(unsigned cell) {
    if (0<cell && requirments->count>cell)
        return this->BuildingInventory+cell;
    return nullptr;
}

ActionResult Building::action()
{
    return ActionResult::OK;
}

bool Building::isFull() {
    for (unsigned i = 0; i < requirments->count; i++)
        if (BuildingInventory[i].isFull())
            return true;

    return false;
}

bool Building::isFull(int ceil) {
    for (unsigned i = 0; i < min(requirments->count, ceil); i++)
        if (BuildingInventory[i].isFull())
            return true;

    return false;
}

#if DLEVEL==0
    #include "iostream"
    void Building::printInventory()
    {
        for (unsigned i = 0; i < requirments->count; i++)
        std::cout<<BuildingInventory[i].getId()<<' '<<BuildingInventory[i].get_quantity()<<'\n';
    }
#endif

Connection::Connection()
{
    to=nullptr;
    from=std::vector<Building*>(0);
}

const Connection* Building::get_Connection()
{
    return &this->con;
}