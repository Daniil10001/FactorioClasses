//
// Created by  Владимир Малахов on 14.02.2025.
// Done some reworks by Daniil on same date
//

#include "factory.hpp"
#include "material.hpp"
#include "services.hpp"
#include "object.hpp"
#include "json_communicate.hpp"
//#include "new" ????????


factory::factory(unsigned int level, unsigned id, point<ll> position):building(id, position) {
    this->level = level;
    bool is_producing = false;


    this->requirments = json_communicate::getRequirmentsById(id);
    this->BuildingInventory = new Material[this->requirments->count];
    
    for(int i=0;i<this->requirments->count;i++)
        BuildingInventory->ChangeId(this->requirments->ids[i]);

    this->factoryMaterialsStart = 2; //Needed to be grabbed from json by id of factory type
}

State factory::get_state() {
    return this->state;
}

ActionResult factory::put_material(Material *m) {
    for (int i = 0; i < requirments->count; i++) {
        if (requirments->ids[i] == m->getId()) {
            BuildingInventory[i] + *m;
            return ActionResult::OK;
        }
    }
    return ActionResult::BAD;
}

Material* factory::get_material(int cell) {
    if (0<cell && requirments->count>cell)
        return this->BuildingInventory+cell;
    return nullptr;
}

ActionResult factory::action() {
    /*if (state == State::OK) //wtf, guy, it is metod that use factory to do something
        if (BuildingInventory->isFull()) {
            state = State::Full;
            return state;
        }

    if (state == State::NotEnoughMaterial) {
        
    }*/
   return ActionResult::OK;
}

void factory::proceed() {

}