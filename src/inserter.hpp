#ifndef inserter_hpp__
#define inserter_hpp__
#include "building.hpp"

class Inserter: public Building
{
protected:
    ID<> idfilt;
    Direction hand_dir;
public:
    constexpr static Types const type=Types::Inserter; 
    Inserter(unsigned id, point<ll> position, Direction d);

    ActionResult put_material(Material *) final {throw "bad function for sinserter";};
    Material* get_material(ID<>) final {throw "bad function for sinserter";};
    Material* get_material() final {throw "bad function for sinserter";};

    ~Inserter();

    ActionResult set_materialFilt(unsigned id);

    void setFilt(ID<> id);
    //bool canDoAction() final;
    ActionResult action() final;
    ActionResult actionMove() final;

    void rotate();
    const Direction& get_handDir();
};


#endif