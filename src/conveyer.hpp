#ifndef conveyer_hpp__
#define conveyer_hpp__

#include "building.hpp"
#include <set>

class Conveyer: public Building
{
    public:

    virtual Types type() const {return Types::Conveyer;}

    Conveyer(unsigned id, point<ll> position, Direction d);

    void setDirectionFrom(Direction d);

    ActionResult put_material(Material *m) final;

    Material* get_material(ID<> id) final;

    Material* get_material() final;

   // bool canDoAction();

    ActionResult action() final;

    ActionResult actionMove() final; //move items to another

    ActionResult put_material(short row, Material *m, Conveyer* prev);
};


#endif