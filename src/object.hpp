#ifndef object_hpp__
#define object_hpp__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "interactioninterfaces.hpp"

class Object
{
protected:
    ID<> id;
    point<ll> p;
    point<unsigned> size;


    bool initilised;
public:
    virtual Types type() const {return Types::Object;}
    bool isGhost = false; // needed while placing new objects

    //Object():initilised(0){};
    Object(unsigned x_size, unsigned y_size);

    Object(ID<> id);

    virtual ~Object();


    //void setPosition(float x, float y, float pixels_per_tile);

    const ID<>& getId();

    void setPosition(point<ll> pos);

    // position in tiles and stored in game's map
    const point<ll>& getPosition();

    const point<unsigned>& getSize();


};

#endif