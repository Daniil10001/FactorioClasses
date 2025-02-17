//
// Created by  Владимир Малахов on 14.02.2025.
// Done some reworks by Daniil on same date
//

#ifndef factory_hpp__
#define factory_hpp__

#include "building.hpp"

class Factory: public Building {
private:
    unsigned int level;
    State state=State::OK;
    unsigned factoryMaterialsStart;
    ll processingTimeStart;
public:
    Factory(unsigned int level, unsigned id, point<ll> position);

    State get_state();

    //ActionResult put_material(Material *m);

    // -1 is product
    //Material* get_material(unsigned cell);

    ActionResult action();

    bool isEnoughIngridients();

    // produce materials
    void produce();
};




#endif //FACTORIO_FACTORY_H
