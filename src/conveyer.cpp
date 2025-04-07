#include"conveyer.hpp"

Conveyer::Conveyer(unsigned id, point<ll> position, Direction d):Building(id,position,d), from(d.mirrored())
{
    BuildingInventory=new Material[4];
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

Material* Building::get_material() {
    for (unsigned cell=0;cell<4;cell++)
        if (this->BuildingInventory[cell].get_quantity()>0) return this->BuildingInventory+cell;
    return nullptr;
}