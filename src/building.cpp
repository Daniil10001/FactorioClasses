#include"building.hpp"
#include <assert.h>
//#include"iostream"
/*Building::Building()
{
}*/

Building::Building(unsigned id, point<ll> position, Direction d) :
    Object(id),requirments(nullptr),  BuildingInventory(nullptr), direction(d), cooldpown(0)
{
    //std::cout<<"init "<<this<<std::endl;
    setPosition(position);
    this->id=id;
}

Building::~Building()
{
    if (BuildingInventory!=nullptr) delete[] BuildingInventory;
    if (requirments!=nullptr) delete requirments;
}

unsigned Building::get_material_quantity(ID<> id) const
{
    for (unsigned i=0;i<requirments->count;i++)
        if(BuildingInventory[i].getId()>=id)
            return BuildingInventory[i].get_quantity();
    return 0;
}

unsigned Building::get_material_maxCapicy(ID<> id) const
{
    for (unsigned i=0;i<requirments->count;i++)
        if(BuildingInventory[i].getId()>=id)
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

//#include<iostream>
ActionResult Building::put_material(Material *m) {
    //std::cout<<"st added\n";
    for (unsigned i = 0; i < requirments->count; i++) {
        //std::cout<<requirments->ids[i].id<<' '<< m->getId().id<< ' '<< (requirments->ids[i] == m->getId()) <<"\n";
        if (requirments->ids[i] == m->getId() && BuildingInventory[i].get_quantity()<BuildingInventory[i].get_maxquantity()) {
            //std::cout<<"added\n";
            return BuildingInventory[i] + *m;
        }
    }
    return ActionResult::BAD;
}

Material* Building::get_material(ID<> id) {
    if (id.id==0) return get_material();
    for (unsigned cell=0;cell<this->requirments->count;cell++)
        if (this->BuildingInventory[cell].getId()>=id) return this->BuildingInventory+cell;
    return nullptr;
}

//#include<iostream>
Material* Building::get_material() {
    //std::cout<<"get_mater\n";
    for (unsigned cell=0;cell<this->requirments->count;cell++)
        if (this->BuildingInventory[cell].get_quantity()>0 && this->requirments->consumes[cell]<0) return this->BuildingInventory+cell;
    for (unsigned cell=0;cell<this->requirments->count;cell++)
        if (this->BuildingInventory[cell].get_quantity()>0) return this->BuildingInventory+cell;
    return nullptr;
}

ActionResult Building::action()
{
    return ActionResult::OK;
}

ActionResult Building::actionMove()
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
        std::cout<<BuildingInventory[i].getId().id<<' '<<BuildingInventory[i].get_quantity()<<'\n';
    }
#endif

//#include<iostream>
const std::vector<Material> Building::getInventory() const
{
    std::vector<Material> v;
    //std::cout<<this->BuildingInventory<<" "<<this<<" "<<requirments->count<<std::endl;
    for (unsigned i = 0; i < requirments->count; i++) v.push_back(BuildingInventory[i]);
    return v;
}

//connection segment
//---------------------------------------------------------------

Connection::Connection(ICarryObj* me):me(me){}

ActionResult Connection::AddConnectionTo(ICarryObj* to)
{
    if (this->to.size()==this->maxToCount) return ActionResult::BAD;
    this->to.insert(to);
    return ActionResult::OK;
}

ActionResult Connection::DeleteConnectionTo(ICarryObj* to)
{
    if (this->to.size()==0) return ActionResult::BAD;
    if (this->to.find(to)==this->to.end()) return ActionResult::BAD;
    this->to.erase(to);
    return ActionResult::OK;
}

ActionResult Connection::AddConnectionFrom(ICarryObj* from)
{
    if (this->from.size()==this->maxFromCount) return ActionResult::BAD;
    this->from.insert(from);
    return ActionResult::OK;
}

ActionResult Connection::DeleteConnectionFrom(ICarryObj* from)
{
    if (this->from.size()==0) return ActionResult::BAD;
    if (this->from.find(from)==this->from.end()) return ActionResult::BAD;
    this->from.erase(from);
    return ActionResult::OK;
}



Connection::~Connection()
{
    //std::cout<<"Deleting connections "<<this<<" "<<this->me<<std::endl;
    for (ICarryObj* b:this->to)
        for (short c=0;c!=Connections::Count;c++)
        {
            //std::cout<<c<<' '<<b<<std::endl;
            //std::cout<<"Discon from "<<b<<" "<<c<<" "<<b->get_Connection((Connections)c)<<'\n';
            b->get_Connection((Connections)c)->DeleteConnectionFrom(this->me);
        }
    for (ICarryObj* b:this->from)
        for (short c=0;c!=Connections::Count;c++)
        {
            //std::cout<<"Discon to "<<b<<" "<<c<<" "<<b->get_Connection((Connections)c)<<'\n';
            b->get_Connection((Connections)c)->DeleteConnectionTo(this->me);
        }
    //std::cout<<"comletle"<<std::endl;
}

const std::set<ICarryObj*>& Connection::GetConnectionsTo()
{
    return this->to;
}

const std::set<ICarryObj*>& Connection::GetConnectionsFrom()
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

ActionResult MakeConnStrait(ICarryObj* from, ICarryObj* to, Connections p)
{
    if (from==to) throw std::invalid_argument("Can not connect same thing!");
    if (p==Connections::Standart)
        throw std::invalid_argument("Invalid use of MakeConnStrait");
    if (from->get_Connection(Connections::Standart)->GetConnectionsTo().count(to)==0)
        throw std::invalid_argument("In MakeConnStrait. You need to add Standart connection before!");
    return MakeConnStrait(from->get_Connection(p),to->get_Connection(p));
}

ActionResult MakeConnForward(ICarryObj* from, ICarryObj* to, Connections p)
{
    if (from==to) throw std::invalid_argument("Can not connect same thing!");
    if (p==Connections::Standart)
        throw std::invalid_argument("Invalid use of MakeConnForward");
    if(from->get_Connection(Connections::Standart)->GetConnectionsTo().count(to)==0)
        throw std::invalid_argument("In MakeConnForward. You need to add Standart connection before!");
    return MakeConnForward(from->get_Connection(p),to->get_Connection(p));
}

ActionResult MakeConnFull(ICarryObj* from, ICarryObj* to, Connections p)
{
    if (from==to) throw std::invalid_argument("Can not connect same thing!");
    if(MakeConnStrait(from->get_Connection(p),to->get_Connection(p))==ActionResult::OK)
    {
        if (MakeConnForward(from->get_Connection(p),to->get_Connection(p))==ActionResult::BAD)
        {
            from->get_Connection(p)->DeleteConnectionTo(to->get_Connection(p)->me);
            return ActionResult::BAD;
        }
    }
    else return ActionResult::BAD;
    return ActionResult::OK;
}


// dummy class sthings
//---------------------------------------------------------------

State Dummy::get_state()
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

Material* Dummy::get_material(ID<> id) {
    if (id==this->m.getId())
        return &this->m;
    return nullptr;
}

unsigned Dummy::get_material_quantity(ID<> id) const
{
    if(m.getId()==id)
        return m.get_quantity();
    return 0;
}

unsigned Dummy::get_material_maxCapicy(ID<> id) const
{
    if(m.getId()==id)
        return m.get_maxquantity();
    return 0;
}

const std::vector<Material> Dummy::getInventory() const
{
    std::vector<Material> v;
    v.push_back(m);
    return v;
}