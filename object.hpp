#ifndef object_hpp__
#define object_hpp__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "interactioninterfaces.hpp"


class Object
{
protected:
    unsigned id;
    point<ll> p;
    point<unsigned> size;
    bool initilised;
    sf::Sprite sprite;
public:
    //Object():initilised(0){};
    Object(unsigned x_size, unsigned y_size, sf::Texture& texture);

    Object(unsigned id);

    virtual ~Object();


    //void setPosition(float x, float y, float pixels_per_tile);


    void setPosition(point<ll> pos);

    // position relative to window and stored in SFML's sf::Sprite
    const sf::Vector2<float> getWindowPosition();

    // position in tiles and stored in game's map
    const point<ll>& getGridPosition();

    const point<unsigned>& getSize();


};

#endif