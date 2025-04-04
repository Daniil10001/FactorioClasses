#ifndef inserter_hpp__
#define inserter_hpp__
#include "building.hpp"

class Inserter: public Building
{
protected:
    unsigned idfilt;
    Direction hand_dir;
public:
    Inserter(unsigned id, point<ll> position, Direction d);

    ActionResult put_material(Material *) final {throw "bad function for sinserter";};
    Material* get_material(unsigned) final {throw "bad function for sinserter";};
    Material* get_material() final {throw "bad function for sinserter";};

    ~Inserter();

    ActionResult set_materialFilt(unsigned id);

    ActionResult action() final;
    ActionResult action_move() final;

    void rotate();
    const Direction& get_handDir();
};


#endif