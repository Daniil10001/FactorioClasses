//
// Created by  Владимир Малахов on 14.02.2025.
//

#include "factory.h"
#include "services.h"
#include "json_communicate.h"
#include "new"


factory::factory(unsigned int level, unsigned capacity, unsigned productId) {
    this->level = level;
    bool is_producing = false;



    this->BuildingInventory = new Material {0, productId};
    this->requirments = json_communicate::getRequirmentsById(productId);

    factoryMaterials = static_cast<Material*>(operator new[](requirments->count * sizeof(Material)));

    for (int i = 0; i < requirments->count; i++)
        new (&factoryMaterials[i]) Material(0, requirments->ids[i]);


}

State factory::get_state() {
    return this->state;
}

ActionResult factory::put_material(Material *m) {
    for (int i = 0; i < requirments->count; i++) {
        if (requirments->ids[i] == m->getId()) {
            factoryMaterials[i] + *m;
            return ActionResult::OK;
        }
    }
    return ActionResult::BAD;
}

Material* factory::get_material(int cell) {
    if (cell == -1)
        return BuildingInventory;

    return &factoryMaterials[cell];
}

State factory::action() {
    if (state == State::OK)
        if (BuildingInventory->isFull()) {
            state = State::Full;
            return state;
        }

    if (state == State::NotEnoughMaterial) {
        
    }
}

void factory::proceed() {

}