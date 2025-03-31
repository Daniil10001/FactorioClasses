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


constexpr const char lvl[]="level";
constexpr const char cldn[]="cooldown";

Factory::Factory(unsigned id, point<ll> position, Direrctions d):Building(id, position,d) {
    this->level =json_communicate::get_property<unsigned,Factory,Checking::size_a(lvl),lvl>(id);//get from json

    this->requirments = json_communicate::getRequirementsById(id);
    this->BuildingInventory = new Material[this->requirments->count];
    
    for(unsigned i=0;i<this->requirments->count;i++)
        (BuildingInventory+i)->ChangeId(this->requirments->ids[i]);

    this->cooldpown=json_communicate::get_property<float,Factory,Checking::size_a(cldn),cldn>(id);
    this->factoryMaterialsStart = 2; //Needed to be grabbed from json by id of factory type
}

State Factory::get_state() {
    return this->state;
}

bool Factory::isEnoughIngridients() const{
    for (unsigned i = 0; i < requirments->count; i++) {
        if ((unsigned)requirments->consumes[i] > BuildingInventory[i].get_quantity()) {
            return false;
        }
    }
    return true;
}

ActionResult Factory::action() {
    if (!isEnoughIngridients()) {
        state = State::NotEnoughMaterial;
        return ActionResult::BAD;
    }

    // if () state = State::Busy
    state = State::OK;


   return ActionResult::OK;
}

void Factory::produce() {
    if (state == State::OK) {
        for (unsigned i = 0; i < requirments->count; i++)
            BuildingInventory[i] -= requirments->consumes[i];
    }

}