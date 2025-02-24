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
    Building* to;
    std::vector<Building*> from;
public:
    Connection();
    void AddConnectionTo();
    void AddConnectionFrom();
    void DeleteConnectionTo();
    void DeleteConnectionFrom();
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

    MaterialList get_requirments();

    unsigned get_material_quantity (unsigned id) const;

    unsigned get_material_maxCapicy(unsigned id) const;

    const Connection* get_Connection();

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(unsigned cell);
    
    virtual ActionResult action();

    bool isFull();

    bool isFull(int ceil);
};



#endif