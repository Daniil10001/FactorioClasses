#include"Inserter.hpp"

Inserter::Inserter(unsigned id, point<ll> position, Direction d):Building(id, position, d), idfilt(0), hand_dir(d)
{
    BuildingInventory = new Material;
}

ActionResult Inserter::set_materialFilt(unsigned cell)
{
    this->idfilt=cell;
    return ActionResult::OK;
}

ActionResult Inserter::action()
{
    if (BuildingInventory->get_quantity()!=0) return ActionResult::BAD;
    *BuildingInventory + *(*con[Connections::Chain]->GetConnectionsFrom().begin())->get_material(idfilt);
    return ActionResult::OK;
}

ActionResult Inserter::action_move()
{
    if (BuildingInventory==nullptr) return ActionResult::BAD;
    (*con[Connections::Chain]->GetConnectionsTo().begin())->put_material(BuildingInventory);
    if (BuildingInventory->get_quantity()==0) BuildingInventory->ChangeId(0);
    if (BuildingInventory->get_quantity()==0) return ActionResult::BAD;
    return ActionResult::OK;
}

void Inserter::rotate()
{
    hand_dir.mirror();
}

const Direction& Inserter::get_handDir()
{
    return hand_dir;
}