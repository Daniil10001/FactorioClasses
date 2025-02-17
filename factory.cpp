//
// Created by  Владимир Малахов on 14.02.2025.
// Done some reworks by Daniil on same date
//

#include "factory.hpp"
#include "material.hpp"
#include "services.hpp"
#include "object.hpp"
#include "jsoncommunicate.hpp"
//#include "new" ????????


Factory::Factory(unsigned int level, unsigned id, point<ll> position):Building(id, position) {
    this->level = level;
    bool is_producing = false;

    FactoryProduct = new Material(0, id);
    this->requirments = json_communicate::getRequirmentsById(id);
    this->BuildingInventory = new Material[this->requirments->count];
    
    for(unsigned i=0;i<this->requirments->count;i++)
        (BuildingInventory+i)->ChangeId(this->requirments->ids[i]);

    this->factoryMaterialsStart = 2; //Needed to be grabbed from json by id of factory type
}

State Factory::get_state() {
    return this->state;
}

bool Factory::isEnoughIngridients() {
    for (int i = 0; i < requirments->count; i++) {
        if (requirments->consumes[i] > BuildingInventory[i].get_quantity()) {
            return false;
        }
    }
    return true;
}

ActionResult Factory::put_material(Material *m) {
    for (unsigned i = 0; i < requirments->count; i++) {
        if (requirments->ids[i] == m->getId()) {
            BuildingInventory[i] + *m;
            return ActionResult::OK;
        }
    }
    return ActionResult::BAD;
}

Material* Factory::get_material(unsigned cell) {
    if (0<cell && requirments->count>cell)
        return this->BuildingInventory+cell;
    if (cell >= 0)
        return this->FactoryProduct;

    return nullptr;
}

ActionResult Factory::action() {
    switch (state) {
        case State::NotEnoughMaterial:
            if (!isEnoughIngridients())
                break;
            state = State::OK;
            break;
    }
    if (state == State::OK) {//wtf, guy, it is metod that use factory to do something
        if (FactoryProduct->isFull()) {
            state = State::Full;
            return ActionResult::BAD;
        }

        if (!isEnoughIngridients()) {
            state = State::NotEnoughMaterial;
            return ActionResult::BAD;
        }


    }

    if (state == State::NotEnoughMaterial) {
        for (int i = 0; i < factoryMaterialsStart; i++);
    }
   return ActionResult::OK;
}

void Factory::proceed() {
    for (unsigned i=0;i<requirments->count;i++)
        BuildingInventory[i]-=requirments->consumes[i];
}