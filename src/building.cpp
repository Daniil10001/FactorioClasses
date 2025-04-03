#include"building.hpp"
#include <assert.h>
//#include"iostream"
/*Building::Building()
{
}*/

Building::Building(unsigned id, point<ll> position, Direction d) :
    Object(id),requirments(nullptr),  BuildingInventory(nullptr), direction(d)
{
   // std::cout<<"init "<<this<<std::endl;
    setPosition(position);
    this->id=id;
    for (Connection*& cn:this->con)  cn=new Connection(this);
}

Building::~Building()
{
    if (BuildingInventory!=nullptr) delete[] BuildingInventory;
    if (requirments!=nullptr) delete requirments;
    for (Connection* c:this->con)  delete c;

}

unsigned Building::get_material_quantity(unsigned id) const
{
    for (unsigned i=0;i<requirments->count;i++)
        if(requirments->ids[i]==id)
            return BuildingInventory[i].get_quantity();
    return 0;
}

unsigned Building::get_material_maxCapicy(unsigned id) const
{
    for (unsigned i=0;i<requirments->count;i++)
        if(requirments->ids[i]==id)
            return BuildingInventory[i].get_maxquantity();
    return 0;
}


State Building::get_state()
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

Material* Building::get_material(unsigned id) {
    if (id==0) return get_material();
    for (unsigned cell=0;cell<this->requirments->count;cell++)
        if (this->BuildingInventory[cell].getId()==id) return this->BuildingInventory+cell;
    return nullptr;
}

Material* Building::get_material() {
    for (unsigned cell=0;cell<this->requirments->count;cell++)
        if (this->BuildingInventory[cell].get_quantity()>0) return this->BuildingInventory+cell;
    return nullptr;
}

ActionResult Building::action()
{
    return ActionResult::OK;
}

ActionResult Building::action_move()
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
//---------------------------------------------------------------

Connection::Connection(Building* me):me(me){}

ActionResult Connection::AddConnectionTo(Building* to)
{
    if (this->to.size()==this->maxToCount) return ActionResult::BAD;
    this->to.insert(to);
    return ActionResult::OK;
}

ActionResult Connection::DeleteConnectionTo(Building* to)
{
    if (this->to.size()==0) return ActionResult::BAD;
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
    if (this->from.size()==0) return ActionResult::BAD;
    if (this->from.find(from)==this->from.end()) return ActionResult::BAD;
    this->from.erase(from);
    return ActionResult::OK;
}



Connection::~Connection()
{
    //std::cout<<"dell "<<this->me<<std::endl;
    for (Building* b:this->to)
        for (short c=0;c!=Connections::Count;c++)
        {
            //std::cout<<c<<' '<<b<<std::endl;
            b->get_Connection((Connections)c)->DeleteConnectionFrom(this->me);
        }
    for (Building* b:this->from)
        for (short c=0;c!=Connections::Count;c++)
            b->get_Connection((Connections)c)->DeleteConnectionTo(this->me);
    //std::cout<<"comletle"<<std::endl;
}

const std::set<Building*>& Connection::GetConnectionsTo()
{
    return this->to;
}

const std::set<Building*>& Connection::GetConnectionsFrom()
{
    return this->from;
}

ActionResult MakeConnStrait(Connection* from, Connection* to)
{
    if (from->to.size()==from->maxToCount) return ActionResult::BAD;
    from->AddConnectionTo(to->me);
    return  ActionResult::OK;
}

ActionResult MakeConnForward(Connection* from, Connection* to)
{
    if (to->from.size()==to->maxFromCount) return ActionResult::BAD;
    to->AddConnectionFrom(from->me);
    return  ActionResult::OK;
}

ActionResult MakeConnStrait(Building* from, Building* to, Connections p)
{
    assert(p!=Connections::Standart);
    assert(from->get_Connection(Connections::Standart)->GetConnectionsTo().count(to)!=0);
    return MakeConnStrait(from->get_Connection(p),to->get_Connection(p));
}

ActionResult MakeConnForward(Building* from, Building* to, Connections p)
{
    assert(p!=Connections::Standart);
    assert(from->get_Connection(Connections::Standart)->GetConnectionsTo().count(to)!=0);
    return MakeConnForward(from->get_Connection(p),to->get_Connection(p));
}

ActionResult MakeConnFull(Building* from, Building* to, Connections p)
{
    if(MakeConnStrait(from->get_Connection(p),to->get_Connection(p))==ActionResult::OK)
    {
        if (MakeConnForward(from->get_Connection(p),to->get_Connection(p))==ActionResult::BAD)
        {
            from->get_Connection(p)->DeleteConnectionTo(to->get_Connection(p)->me);
            return ActionResult::BAD;
        }
    }
    return ActionResult::OK;
}


// dummy class sthings
//---------------------------------------------------------------

Connection * Dummy::get_Connection(Connections p)
{
    if (p>=Connections::Count) return nullptr;
    return this->con[p];
}

State Dummy::get_state() const
{
    if (m.get_quantity()==m.get_maxquantity()) return State::Full;
    return State::OK;
}

ActionResult Dummy::put_material(Material *m) {
    return this->m + *m;
}

Material* Dummy::get_material() {
    return &this->m;
}

unsigned Dummy::get_material_quantity(unsigned id) const
{
    if(m.getId()==id)
        return m.get_quantity();
    return 0;
}

unsigned Dummy::get_material_maxCapicy(unsigned id) const
{
    if(m.getId()==id)
        return m.get_maxquantity();
    return 0;
}