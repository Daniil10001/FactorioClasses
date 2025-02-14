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
    building(unsigned id);

    virtual State get_state();

    MaterialList get_requirments();

    int get_material_quantity(unsigned id);

    int get_material_maxCapicy(unsigned id);

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(int cell);
    
    virtual ActionResult action();
};


#endif