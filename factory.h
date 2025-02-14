//
// Created by  Владимир Малахов on 14.02.2025.
//

#ifndef FACTORIO_FACTORY_H
#define FACTORIO_FACTORY_H

#include "building.hpp"

class factory: building {
private:
    unsigned int level;
    State state;
    Material* factoryMaterials;

    ll processingTimeStart;
public:
    factory(unsigned int level, unsigned capacity, unsigned productId);

    State get_state();

    ActionResult put_material(Material *m);

    // -1 is product
    Material* get_material(int cell);

    State action();

    // method launching after
    void proceed();
};




#endif //FACTORIO_FACTORY_H
