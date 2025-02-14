#ifndef building_hpp__
#define building_hpp__

#include "object.hpp"
#include "material.hpp"
#include "interactioninterfaces.hpp"

class building: public Object
{
protected:
    unsigned id;
    MaterialList* requirments;

    // product if assigned to a factory
    Material* BuildingInventory;
public:
    building();
    building(unsigned id, point<ll> position);

    virtual State get_state();

    MaterialList get_requirments();

    unsigned get_material_quantity(unsigned id);

    unsigned get_material_maxCapicy(unsigned id);

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(unsigned cell);
    
    virtual ActionResult action();
};


#endif