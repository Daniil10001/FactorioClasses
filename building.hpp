#ifndef building_hpp__
#define building_hpp__

#include <vector> //we need to use std here to make code smaller
#include <set>
#include <map>
#include "object.hpp"
#include "material.hpp"
#include "interactioninterfaces.hpp"



class Building;
ActionResult MakeConnection(Building* from, Building* to, int p);

class Connection
{
private:
    Building* me;
    unsigned maxToCount=255;
    unsigned maxFromCount=255;
    std::set<Building*> to;
    std::set<Building*> from;
public:
    //Connection();
    Connection(Building* me);
    ActionResult AddConnectionTo(Building* to);
    ActionResult AddConnectionFrom(Building* from);
    ActionResult DeleteConnectionTo(Building* to);
    ActionResult DeleteConnectionFrom(Building* from);
    const std::set<Building*>& GetConnectionsTo();
    const std::set<Building*>& GetConnectionsFrom();
    
    friend ActionResult MakeConnection(Connection* from, Connection* to);
    friend ActionResult MakeConnection(Building* from, Building* to, int p);
    
    ~Connection(); //Works only with standart connections. Chain connection do not apply
};

/* user
 * user 100 дерева
 * юзер конвейер - акшн - 10 дерева
 * юзер может использовать?
 * может - 10
 * не может - ошибка
*/

class Building: public Object
{
protected:
    std::map<int,Connection> con;

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

    MaterialList const* get_requirments();

    unsigned get_material_quantity (unsigned id) const;

    unsigned get_material_maxCapicy(unsigned id) const;

    Connection * get_Connection(int p);

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(unsigned cell);
    
    virtual ActionResult action();

    bool isFull();

    bool isFull(unsigned ceil);
};



#endif