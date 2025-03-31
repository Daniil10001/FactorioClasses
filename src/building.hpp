#ifndef building_hpp__
#define building_hpp__

#include <vector> //we need to use std here to make code smaller
#include <set>
#include <array>
#include "object.hpp"
#include "material.hpp"
#include "interactioninterfaces.hpp"



class Building;
ActionResult MakeConnStrait(Building* from, Building* to, Connections p);
ActionResult MakeConnForward(Building* from, Building* to, Connections p);
ActionResult MakeConnFull(Building* from, Building* to, Connections p);

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
    
    friend ActionResult MakeConnStrait(Connection* from, Connection* to);
    friend ActionResult MakeConnForward(Connection* from, Connection* to);
    friend ActionResult MakeConnStrait(Building* from, Building* to, Connections p);
    friend ActionResult MakeConnForward(Building* from, Building* to, Connections p);
    friend ActionResult MakeConnFull(Building* from, Building* to, Connections p);
    
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
    std::array<Connection*,Connections::Count> con;

    MaterialList* requirments;

    //requirments and product if assigned to a factory
    Material* BuildingInventory;

    Direction direction;

 public:
    constexpr static Types const type=Types::Building; 
    //Building();
    Building(unsigned id, point<ll> position, Direction d);
    ~Building();
#if DLEVEL==0
    void printInventory();
#endif
    virtual State get_state() const;

    MaterialList const* get_requirments();

    unsigned get_material_quantity (unsigned id) const;

    unsigned get_material_maxCapicy(unsigned id) const;

    Connection * get_Connection(Connections p);

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(unsigned cell);
    
    virtual ActionResult action();

    virtual ActionResult action_move(); //move items

    bool isFull();

    bool isFull(unsigned ceil);
};



#endif