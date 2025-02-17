#ifndef building_hpp__
#define building_hpp__

#include "object.hpp"
#include "material.hpp"
#include "interactioninterfaces.hpp"

class Building: public Object
{
protected:
    unsigned id;

    MaterialList* requirments;

    // product if assigned to a factory
    Material* BuildingInventory;
 public:
    Building();
    Building(unsigned id, point<ll> position);
    ~Building();
#if DLEVEL==0
    void printInventory();
#endif
    virtual State get_state();

    MaterialList get_requirments();

    unsigned get_material_quantity(unsigned id);

    unsigned get_material_maxCapicy(unsigned id);

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(unsigned cell);
    
    virtual ActionResult action();

    bool isFull();

    bool isFull(int ceil);
};


#endif