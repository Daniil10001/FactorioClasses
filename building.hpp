#ifndef building_hpp__
#define building_hpp__

#include "object.hpp"
#include "material.hpp"
#include "interactioninterfaces.hpp"

class building: public Object
{
private:
    int id;
    MaterialList requirments;
    
    Material* BuildingInventory;
public:
    building(ll x,ll y, int id);

    virtual State get_state();

    MaterialList get_requirments();

    int get_material_quantity(int id);

    int get_material_maxCapicy(int id);

    virtual ActionResult put_material(Material *m);
    
    virtual Material get_material(int cell);
    
    virtual ActionResult action();
};


#endif