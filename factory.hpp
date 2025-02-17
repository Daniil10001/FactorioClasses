//
// Created by  Владимир Малахов on 14.02.2025.
// Done some reworks by Daniil on same date
//

#ifndef FACTORIO_FACTORY__
#define FACTORIO_FACTORY__

#include "building.hpp"

class Factory: public Building {
private:
    unsigned int level;
    State state;
    int factoryMaterialsStart;
    Material* FactoryProduct;
    ll processingTimeStart;
public:
    Factory(unsigned int level, unsigned id, point<ll> position);

    State get_state();

    ActionResult put_material(Material *m);

    // -1 is product
    Material* get_material(int cell);

    ActionResult action();

    bool isEnoughIngridients();

    // method launching after
    void proceed();
};




#endif //FACTORIO_FACTORY_H
