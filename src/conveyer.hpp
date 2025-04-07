#ifndef conveyer_hpp__
#define conveyer_hpp__

#include "building.hpp"

class Conveyer: public Building
{
    private:
        Direction from;
    public:

    constexpr static Types const type=Types::Conveyer; 

    Conveyer(unsigned id, point<ll> position, Direction d);

    void setDirectionFrom(Direction d);

    ActionResult put_material(Material *m) final;

    Material* get_material(ID<> id) final;

    Material* get_material() final;

    bool canDoAction();

    ActionResult action();

    ActionResult action_move(); //move items to another
};


#endif