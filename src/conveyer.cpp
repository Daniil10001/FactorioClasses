#include"conveyer.hpp"

Conveyer::Conveyer(unsigned id, point<ll> position, Direction d):Building(id,position,d)
{
    BuildingInventory=new Material[4];
    for (unsigned cell=0; cell<4;cell++) BuildingInventory[cell].setCapacity(1);
    requirments=nullptr;
}

ActionResult Conveyer::put_material(Material *m) {
    for (unsigned i = 0; i < 4; i++) {
        if (BuildingInventory[i].getId() == m->getId() || BuildingInventory[i].getId()==0) {
            return BuildingInventory[i] + *m;
        }
    }
    return ActionResult::BAD;
}

Material* Conveyer::get_material(ID<> id) {
    if (id==0) return get_material();
    for (unsigned cell=0;cell<4;cell++)
        if (this->BuildingInventory[cell].getId()==id) return this->BuildingInventory+cell;
    return nullptr;
}

Material* Conveyer::get_material() {
    for (unsigned cell=0;cell<4;cell++)
        if (this->BuildingInventory[cell].get_quantity()>0) return this->BuildingInventory+cell;
    return nullptr;
}

/*bool Conveyer::canDoAction()
{
    if (con[Connections::Chain]->GetConnectionsTo().size()==0 &&
    get_material()==nullptr) return false;
    return true;
}*/

Directions rotate(Direction main, Direction d)
{
    while ((++main).dir()!=Directions::UP) ++d;
    return d.dir();
}

ActionResult Conveyer::put_material(short row, Material *m, Conveyer* prev)
{
    if (row>1) throw std::invalid_argument("Conveyer cell error!");
    if (get_Connection(Connections::Chain)->GetConnectionsFrom().count(dynamic_cast<ICarryObj*>(prev))) throw std::invalid_argument("Not connected!");
    switch (rotate(this->direction, prev->direction))
    {
        case Directions::UP:
            return BuildingInventory[row]+*m;
        case Directions::LEFT:
            return BuildingInventory[row*2]+*m;
        case Directions::RIGHT:
            return BuildingInventory[row*2+1]+*m;
        default:
            throw std::runtime_error("Something went wrong with conveyer!");
    }
    return ActionResult::BAD;
}

ActionResult Conveyer::action()
{
    return ActionResult::OK;
}

ActionResult Conveyer::actionMove()
{
    if (get_Connection(Connections::Chain)->GetConnectionsTo().size()==1)
        for (int i=0;i<2;i++)
            if (dynamic_cast<Conveyer*>(*get_Connection(Connections::Chain)->GetConnectionsTo().begin()))
                dynamic_cast<Conveyer*>(*get_Connection(Connections::Chain)->GetConnectionsTo().begin())->put_material(i,BuildingInventory+i+2,this);
    else
        throw std::runtime_error("Erorr in chaining conveyer to");
    return ActionResult::OK;
}