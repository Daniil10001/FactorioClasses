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


Factory::Factory(unsigned int level, unsigned id, point<ll> position):Building(id, position) {
    this->level = level;
    bool is_producing = false;

    FactoryProduct = new Material(0, id);
    this->requirments = json_communicate::getRequirmentsById(id);
    this->BuildingInventory = new Material[this->requirments->count];
    
    for(int i=0;i<this->requirments->count;i++)
        BuildingInventory->ChangeId(this->requirments->ids[i]);

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
    for (int i = 0; i < requirments->count; i++) {
        if (requirments->ids[i] == m->getId()) {
            BuildingInventory[i] + *m;
            return ActionResult::OK;
        }
    }
    return ActionResult::BAD;
}

Material* Factory::get_material(int cell) {
    if (0<cell && requirments->count > cell)
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

        case State::
    }
    if (state == State::OK) {//wtf, guy, it is metod that use factory to do something
        if (FactoryProduct->isFull()) {
            state = State::Full;
            return state;
        }

        if (!isEnoughIngridients()) {
            state = State::NotEnoughMaterial;
            return state;
        }


    }

    if (state == State::NotEnoughMaterial) {
        for (int i = 0; i < factoryMaterialsStart)
    }
   return ActionResult::OK;
}

void Factory::proceed() {

}