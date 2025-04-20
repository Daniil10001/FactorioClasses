#include"sessionlogic.hpp"

#include<vector>

const std::set<Object *> SessionHandler::get_layer(ObjectTypes lr) const
{
    return this->objs[lr];
}

ActionResult SessionHandler::delFromLayerB(Object* obj)
{
    if (!this->objs[ObjectTypes::Buildings].count(obj)) return ActionResult::BAD;
    Processing_objects=1;
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
    Processing_objects=0;
    return ActionResult::OK;
}

Object* SessionHandler::findObj(point<ll> p, ObjectTypes layer=ObjectTypes::Buildings)
{
    point<ll> pb;
    point<unsigned> sz;
    for (auto obj: objs[layer])
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
        szb=obj->getSize();
        if (max(pb.x,p.x) >= min(pb.x+szb.x-1,p.x+sz.x-1) && p.x<=pb.x+szb.x-1 && pb.x<=p.x+sz.x-1)
            if (max(pb.y,p.y) >= min(pb.y+szb.y-1,p.y+sz.y-1) && p.y<=pb.y+szb.y-1 && pb.y<=p.y+sz.y-1)
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
    case Types::Chest:
        break;
    case Types::Conveyer:
        p=b->getPosition()+dynamic_cast<Building*>(b)->getDirection().get();
        o=findObj(p);

        if (o==nullptr) o=findObj(p,ObjectTypes::SpecialPoints);
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
        if (o==nullptr) o=findObj(p,ObjectTypes::SpecialPoints);
        if (o==nullptr)
        {
            o=new Dummy(p);
            objs[ObjectTypes::SpecialPoints].insert(o);
        }
        std::cout<<(MakeConnFull(dynamic_cast<ICarryObj*>(b),dynamic_cast<ICarryObj*>(o),Connections::Standart)==ActionResult::OK)<<" mc\n";
        if (!dynamic_cast<Inserter*>(o))  MakeConnStrait(dynamic_cast<ICarryObj*>(b),dynamic_cast<ICarryObj*>(o),Connections::Chain);

        p=b->getPosition()-dynamic_cast<Building*>(b)->getDirection().get();
        o=findObj(p);
        if (o==nullptr) o=findObj(p,ObjectTypes::SpecialPoints);
        if (o==nullptr)
        {
            o=new Dummy(p);
            objs[ObjectTypes::SpecialPoints].insert(o);
        }
        MakeConnFull(dynamic_cast<ICarryObj*>(o),dynamic_cast<ICarryObj*>(b),Connections::Standart);
        if (!dynamic_cast<Inserter*>(o))  MakeConnForward(dynamic_cast<ICarryObj*>(o),dynamic_cast<ICarryObj*>(b),Connections::Chain);
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
        //std::cout<<obj<<'\n';
        if (dynamic_cast<Dummy*>(obj))
        {
            for (auto obj_c: dynamic_cast<Dummy*>(obj)->get_Connection(Connections::Standart)->GetConnectionsFrom())
            {
               //std::cout<<obj_c<<'\n';
               MakeConnections(dynamic_cast<Object*>(obj_c));
            }
            for (auto obj_c: dynamic_cast<Dummy*>(obj)->get_Connection(Connections::Standart)->GetConnectionsTo())
            {
               // std::cout<<obj_c<<'\n';
               MakeConnections(dynamic_cast<Object*>(obj_c));
            }
        }
        else throw std::invalid_argument("There are some not dummies in specialpoints layer!");
        objs[ObjectTypes::SpecialPoints].erase(obj);
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
        o = new Factory(id, p, dir);//o = new Factory(id, p, dir);
        break;
    case Types::Inserter:
        o = new Inserter(id, p, dir);//o = new Inserter(id, p, dir);
        break;
    case Types::Chest:
        o = new Chest(id, p, dir);
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
        throw std::runtime_error("Intersection with other buildings!");
    }
    objs[ObjectTypes::Buildings].insert(o);
    ClearDummies(findInters(o->getPosition(),o->getSize(),ObjectTypes::SpecialPoints));
    MakeConnections(o);
    tims.register_timer(o);
    Processing_objects=0;
    return o;
}

SessionHandler::~SessionHandler()
{
    Processing_objects=2;
    for (unsigned i=0;i<ObjectTypes::Count;i++)
        for (auto obj : objs[i])
        {
            std::cout<<"del "<<obj<<'\n';
            delete obj;
        }
}