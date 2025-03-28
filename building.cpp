#include"building.hpp"

/*Building::Building()
{
}*/

Building::Building(unsigned id, point<ll> position, Direrctions d):Object(id), direction(d)
{
    set_cord(position.x,position.y);
    this->id=id;
    for (Connection*& cn:this->con)  cn=new Connection(this);
}

Building::~Building()
{
    delete[] BuildingInventory;
    delete requirments;
    for (Connection* c:this->con)  delete c;

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

MaterialList const*  Building::get_requirments()
{
    return this->requirments;
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

bool Building::isFull(unsigned ceil) {
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

Connection * Building::get_Connection(Connections p)
{
    if (p>=Connections::Count) return nullptr;
    return this->con[p];
}

//connection segment

Connection::Connection(Building* me):me(me){}

ActionResult Connection::AddConnectionTo(Building* to)
{
    if (this->to.size()==this->maxToCount) return ActionResult::BAD;
    this->to.insert(to);
    return ActionResult::OK;
}

ActionResult Connection::DeleteConnectionTo(Building* to)
{
    if (this->to.find(to)==this->to.end()) return ActionResult::BAD;
    this->to.erase(to);
    return ActionResult::OK;
}

ActionResult Connection::AddConnectionFrom(Building* from)
{
    if (this->from.size()==this->maxFromCount) return ActionResult::BAD;
    this->from.insert(from);
    return ActionResult::OK;
}

ActionResult Connection::DeleteConnectionFrom(Building* from)
{
    if (this->from.find(from)==this->from.end()) return ActionResult::BAD;
    this->from.erase(from);
    return ActionResult::OK;
}



Connection::~Connection()
{
    for (Building* b:this->to)
        b->get_Connection(Connections::Standart)->DeleteConnectionFrom(this->me);
    for (Building* b:this->from)
        b->get_Connection(Connections::Standart)->DeleteConnectionTo(this->me);
}

ActionResult MakeConnection(Connection* from, Connection* to)
{
    if (to->from.size()==to->maxFromCount) return ActionResult::BAD;
    if (from->to.size()==from->maxToCount) return ActionResult::BAD;
    to->AddConnectionFrom(from->me);
    from->AddConnectionTo(to->me);
    return  ActionResult::OK;
}

const std::set<Building*>& Connection::GetConnectionsTo()
{
    return this->to;
}

const std::set<Building*>& Connection::GetConnectionsFrom()
{
    return this->from;
}

ActionResult MakeConnection(Building* from, Building* to, Connections p)
{
    return MakeConnection(from->get_Connection(p),to->get_Connection(p));
}
