#include"inserter.hpp"

Inserter::Inserter(unsigned id, point<ll> position, Direction d):Building(id, position, d), idfilt(0), hand_dir(d)
{
    BuildingInventory = new Material[1];
    BuildingInventory->setCapacity(1);
}

Inserter::~Inserter(){}

ActionResult Inserter::set_materialFilt(unsigned cell)
{
    this->idfilt=cell;
    return ActionResult::OK;
}

//#include<iostream>
ActionResult Inserter::action()
{
    if (BuildingInventory->get_quantity()!=0) return ActionResult::BAD;
    //std::cout<<con[Connections::Chain]->GetConnectionsFrom().size()<<std::endl;
    //std::cout<<" |id:"<<(*con[Connections::Chain]->GetConnectionsFrom().begin())->get_material(ID<>(0))->getId().id<<"| ";
    if (con[Connections::Chain]->GetConnectionsFrom().size()!=1) throw std::runtime_error("Erorr in chaining inserter from");
    Material *it = (*con[Connections::Chain]->GetConnectionsFrom().begin())->get_material(idfilt);
    //fast check
    //std::cout<<" |itc"<<(it!=nullptr)<<"| "<<it<<" ";
    //std::cout<<" |id "<<BuildingInventory->getId().id<<" "<<it->getId().id<<"| ";
    return (it!=nullptr?*BuildingInventory + *it:ActionResult::BAD);
}

ActionResult Inserter::actionMove()
{
    if (BuildingInventory==nullptr) return ActionResult::BAD;
    //std::cout<<" |id:"<<BuildingInventory->getId().id<<"| ";
    if (con[Connections::Chain]->GetConnectionsTo().size()!=1) throw std::runtime_error("Erorr in chaining inserter to");
    (*con[Connections::Chain]->GetConnectionsTo().begin())->put_material(BuildingInventory);
    if (BuildingInventory->get_quantity()!=0) return ActionResult::BAD;
    return ActionResult::OK;
}

void Inserter::rotate()
{
    hand_dir.mirror();
}

void Inserter::setFilt(ID<> id)
{
    this->idfilt = id;
}

/*bool Inserter::canDoAction()
{
    if (idfilt==0) throw std::invalid_argument("In inserter there filter set to none!");
    return (BuildingInventory->get_quantity()>0//(*con[Connections::Chain]->GetConnectionsFrom().begin())->get_material_quantity(idfilt)>0) 
        && ((*con[Connections::Chain]->GetConnectionsTo().begin())->get_material_quantity(idfilt)<(*con[Connections::Chain]->GetConnectionsTo().begin())->get_material_maxCapicy(idfilt)));
}*/

const Direction& Inserter::get_handDir()
{
    return hand_dir;
}