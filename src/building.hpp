#ifndef building_hpp__
#define building_hpp__

#include <vector> //we need to use std here to make code smaller
#include <set>
#include <array>
#include "object.hpp"
#include "material.hpp"
#include "interactioninterfaces.hpp"



class Building;
class ICarryObj;

ActionResult MakeConnStrait(ICarryObj* from, ICarryObj* to, Connections p);
ActionResult MakeConnForward(ICarryObj* from, ICarryObj* to, Connections p);
ActionResult MakeConnFull(ICarryObj* from, ICarryObj* to, Connections p);

class Connection
{
private:
    ICarryObj* me;
    unsigned maxToCount=255;
    unsigned maxFromCount=255;
    std::set<ICarryObj*> to;
    std::set<ICarryObj*> from;
public:
    //Connection();
    Connection(ICarryObj* me);
    ActionResult AddConnectionTo(ICarryObj* to);
    ActionResult AddConnectionFrom(ICarryObj* from);
    ActionResult DeleteConnectionTo(ICarryObj* to);
    ActionResult DeleteConnectionFrom(ICarryObj* from);
    const std::set<ICarryObj*>& GetConnectionsTo();
    const std::set<ICarryObj*>& GetConnectionsFrom();
    
    friend ActionResult MakeConnStrait(Connection* from, Connection* to);
    friend ActionResult MakeConnForward(Connection* from, Connection* to);
    friend ActionResult MakeConnStrait(ICarryObj* from, ICarryObj* to, Connections p);
    friend ActionResult MakeConnForward(ICarryObj* from, ICarryObj* to, Connections p);
    friend ActionResult MakeConnFull(ICarryObj* from, ICarryObj* to, Connections p);
    
    ~Connection(); //Works only with standart connections. Chain connection do not apply
};

/* user
 * user 100 дерева
 * юзер конвейер - акшн - 10 дерева
 * юзер может использовать?
 * может - 10
 * не может - ошибка
*/

class ICarryObj
{
    protected:
        std::array<Connection*,Connections::Count> con;
    public:
    Connection * get_Connection(Connections p)
    {
        if (p>=Connections::Count) assert(false);
        return this->con[p];
    };

    ICarryObj(){for (Connection*& cn:this->con)  cn=new Connection(this);}
    ~ICarryObj(){for (Connection* c:this->con)  delete c;}

    virtual ActionResult put_material(Material *m)=0;
    
    virtual Material* get_material()=0;

    virtual Material* get_material(ID<> id) = 0;

    virtual unsigned get_material_quantity (ID<> id) const=0;

    virtual unsigned get_material_maxCapicy(ID<> id) const=0;

    virtual State get_state()=0;
};

class Building: public Object, public ICarryObj
{
protected:

    MaterialList* requirments;

    //requirments and product if assigned to a factory
    Material* BuildingInventory;

    Direction direction;

 public:
    constexpr static Types const type=Types::Building; 
    //Building();
    Building(unsigned id, point<ll> position, Direction d);
    virtual ~Building();
#if DLEVEL==0
    void printInventory();
#endif
    virtual State get_state();

    MaterialList const* get_requirments();

    unsigned get_material_quantity (ID<> id) const final;

    unsigned get_material_maxCapicy(ID<> id) const final;

    virtual ActionResult put_material(Material *m);
    
    virtual Material* get_material(ID<> id);

    virtual Material* get_material();

    virtual bool canDoAction()=0;

    virtual ActionResult action();

    virtual ActionResult action_move(); //move items to another

    bool isFull();

    bool isFull(unsigned ceil);
};


class Dummy:public Object, public ICarryObj {
    protected:
        Material m;
    public:
    constexpr static Types const type=Types::Dummy;

    Dummy(point<ll> p):Object(1,1){setPosition(p);}
    
    ActionResult put_material(Material *m) final;
    
    Material* get_material() final;

    Material* get_material(ID<> id) final;

    unsigned get_material_quantity (ID<> id) const final;

    unsigned get_material_maxCapicy(ID<> id) const final;

    State get_state() final;    
};


#endif