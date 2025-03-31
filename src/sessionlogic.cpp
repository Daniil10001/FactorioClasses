#include"sessionlogic.hpp"

const std::set<Object *> SessionHandler::get_layer(ObjectTypes lr) const
{
    return this->objs[lr];
}

ActionResult SessionHandler::delFromLayerB(Object* obj)
{
    if (!this->objs[ObjectTypes::Buildings].count(obj)) return ActionResult::BAD;
    this->objs[ObjectTypes::Buildings].erase(obj);
    this->tims.unregister_timer(obj);   
    for (auto builds: ((Building *)obj)->get_Connection(Connections::Standart)->GetConnectionsTo())
    {
        //do some stuff to unlock
    }
    for (auto builds: ((Building *)obj)->get_Connection(Connections::Standart)->GetConnectionsTo())
    {
        //do some stuff to unlock
    }
    delete obj;
}