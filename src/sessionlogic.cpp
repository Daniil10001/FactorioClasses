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

void SessionHandler::MakeConnections(Object* b)
{
    switch (b->type())
    {
    case Types::Factory:
        break;
    case Types::Conveyer:
        //create one dummy
        break;
    case Types::Inserter:
        //create two dummies
        break;
    default:
        throw std::invalid_argument("Bad call for making connections");
        break;
    }
};