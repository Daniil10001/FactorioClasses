#ifndef building_hpp__
#define building_hpp__

#include <vector> //we need to use std here to make code smaller
#include "object.hpp"
#include "material.hpp"
#include "interactioninterfaces.hpp"

class Building;
class Connection
{
private:
    unsigned maxfromcount;
    Building* to;
    std::vector<Building*> from;
public:
    Connection();
    Connection(unsigned mxfmcnt);
    ActionResult AddConnectionTo(Building* to);
    ActionResult AddConnectionFrom(Building* from);
    ActionResult DeleteConnectionTo();
    ActionResult DeleteConnectionFrom(Building* from);
    Building * const GetConnectionTo();
    const std::vector<Building* const> GetConnectionFrom(); 
};


class Building: public Object
{
protected:
    unsigned id;

    Connection con;

    MaterialList* requirments;

    //requirments and product if assigned to a factory
    Material* BuildingInventory;
 public:
    Building();
    Building(unsigned id, point<ll> position);
    ~Building();
#if DLEVEL==0
    void printInventory();
#endif
    virtual State get_state() const;

    const MaterialList* const get_requirments();

    unsigned get_material_quantity (unsigned id) const;

    unsigned get_material_maxCapicy(unsigned id) const;

    const Connection* get_Connection();

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(unsigned cell);
    
    virtual ActionResult action();

    bool isFull();

    bool isFull(unsigned ceil);
};



#endif