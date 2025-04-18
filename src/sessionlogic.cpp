#include"sessionlogic.hpp"

#include<vector>

const std::set<Object *> SessionHandler::get_layer(ObjectTypes lr) const
{
    return this->objs[lr];
}

ActionResult SessionHandler::delFromLayerB(Object* obj)
{
    if (!this->objs[ObjectTypes::Buildings].count(obj)) return ActionResult::BAD;
    this->objs[ObjectTypes::Buildings].erase(obj);
    this->tims.unregister_timer(obj);
    std::vector<ICarryObj*> stack;
    for (auto builds: ((Building *)obj)->get_Connection(Connections::Standart)->GetConnectionsTo()) stack.push_back(builds);
    for (auto builds: ((Building *)obj)->get_Connection(Connections::Standart)->GetConnectionsTo()) stack.push_back(builds);
    delete obj;
    for (ICarryObj* build: stack)
    {
        if (dynamic_cast<Object*>(build)!=nullptr) throw  std::runtime_error("Something went wrong in navigating building tree!");
        MakeConnections(dynamic_cast<Building*>(build));
    }
    return ActionResult::OK;
}

Object* SessionHandler::findObj(point<ll> p)
{
    point<ll> pb;
    point<unsigned> sz;
    for (auto obj: objs[ObjectTypes::Buildings])
    {
        pb=obj->getPosition();
        sz=obj->getSize();
        if (p.x<=pb.x+sz.x-1 && p.x>=pb.x)
            if (p.y<=pb.y+sz.y-1 && p.y>=pb.y)
                return obj;
    }
    return nullptr;
}

std::set<Object*> SessionHandler::findInters(point<ll> p, point<unsigned> sz, ObjectTypes layer)
{
    std::set<Object*> st;
    point<ll> pb;
    point<unsigned> szb;
    for (auto obj: objs[layer])
    {
        pb=obj->getPosition();
        sz=obj->getSize();
        if (max(pb.x,p.x) > min(pb.x+szb.x,p.x+sz.x))
            if (max(pb.y,p.y) > min(pb.y+szb.y,p.y+sz.y))
                st.insert(obj);
    }
    return st;
}

void SessionHandler::MakeConnections(Object* b)
{
    point<ll> p; Object* o;
    switch (b->type())
    {
    case Types::Factory:
        break;
    case Types::Conveyer:
        p=b->getPosition()+dynamic_cast<Building*>(b)->getDirection().get();
        o=findObj(p);
        if (o==nullptr)
        {
            o=new Dummy(p);
            objs[ObjectTypes::SpecialPoints].insert(o);
        }
        MakeConnFull(dynamic_cast<ICarryObj*>(b),dynamic_cast<ICarryObj*>(o),Connections::Standart);
        if (dynamic_cast<Conveyer*>(o))  MakeConnStrait(dynamic_cast<ICarryObj*>(b),dynamic_cast<ICarryObj*>(o),Connections::Chain);
        break;
    case Types::Inserter:
        p=b->getPosition()+dynamic_cast<Building*>(b)->getDirection().get();
        o=findObj(p);
        if (o==nullptr)
        {
            o=new Dummy(p);
            objs[ObjectTypes::SpecialPoints].insert(o);
        }
        MakeConnFull(dynamic_cast<ICarryObj*>(b),dynamic_cast<ICarryObj*>(o),Connections::Standart);
        if (dynamic_cast<Conveyer*>(o))  MakeConnStrait(dynamic_cast<ICarryObj*>(b),dynamic_cast<ICarryObj*>(o),Connections::Chain);

        p=b->getPosition()-dynamic_cast<Building*>(b)->getDirection().get();
        o=findObj(p);
        if (o==nullptr)
        {
            o=new Dummy(p);
            objs[ObjectTypes::SpecialPoints].insert(o);
        }
        MakeConnFull(dynamic_cast<ICarryObj*>(b),dynamic_cast<ICarryObj*>(o),Connections::Standart);
        if (dynamic_cast<Conveyer*>(o))  MakeConnForward(dynamic_cast<ICarryObj*>(o),dynamic_cast<ICarryObj*>(b),Connections::Chain);
        break;
    default:
        throw std::invalid_argument("Bad call for making connections");
        break;
    }
}

void SessionHandler::ClearDummies(const std::set<Object*> &setobj)
{
    for (auto obj: setobj)
    {
        if (dynamic_cast<Building*>(obj))
            for (auto obj_c: dynamic_cast<Building*>(obj)->get_Connection(Connections::Standart)->GetConnectionsFrom())
            {
               MakeConnections(dynamic_cast<Object*>(obj_c));
            }
        delete obj;
    }
}

Object* SessionHandler::addToLayerB(unsigned id, point<ll> p, Direction dir)
{
    Types T = TypesHandler::getTypeById(id);
    Object* o;
    switch (T)
    {
    case Types::Conveyer:
        o = new Conveyer(id, p, dir);
        break;
    case Types::Factory:
        o = new Conveyer(id, p, dir);
        break;
    case Types::Inserter:
        o = new Conveyer(id, p, dir);
        break;
    default:
    throw std::invalid_argument("Bad call for type that creates in layer buildings!");
        break;
    }
    Processing_objects=1;
    if (findInters(o->getPosition(),o->getSize(),ObjectTypes::Buildings).size()!=0) 
    {
        delete o;
        //return nullptr;
        std::runtime_error("Intersection with other buildings!");
    }
    objs[ObjectTypes::Buildings].insert(o);
    ClearDummies(findInters(o->getPosition(),o->getSize(),ObjectTypes::SpecialPoints));
    MakeConnections(o);
    tims.register_timer(o);
    Processing_objects=0;
    return o;
}