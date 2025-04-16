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

std::set<Object*> SessionHandler::findInters(point<ll> p, point<unsigned> sz)
{
    std::set<Object*> st;
    point<ll> pb;
    point<unsigned> szb;
    for (auto obj: objs[ObjectTypes::Buildings])
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
};

