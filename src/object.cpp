
#include"object.hpp"
#include "jsoncommunicate.hpp"
#include "window.hpp"

constexpr const char xs[]="size_x";
constexpr const char ys[]="size_y";

Object::Object(unsigned x_size, unsigned y_size, sf::Texture& texture) :
    p(0,0),size(x_size,y_size)
{
    this->initilised=true;
}

Object::Object(unsigned id) :
    size(
            json_communicate::get_property<unsigned,Object,Checking::size_a(xs),xs>(id),
            json_communicate::get_property<unsigned,Object,Checking::size_a(ys),ys>(id)
            )
{                   //dummy thin neded to replaced by json
    this->initilised=true;
}



const point<unsigned>& Object::getSize()
{
    return this->size;
}

Object::~Object()
{
    
}

/*void Object::setPosition(float x, float y) {
    sprite.setPosition({x, y});
    p.x = x / (float)pixels_per_tile;
    p.y = y / (float)pixels_per_tile;
}*/

void Object::setPosition(point<long long> pos) {
    p = pos;
//    sprite.setPosition({pos.x / })
}

const point<long long> &Object::getPosition() {
    return p;
}

unsigned int Object::getId() {
    return id;
}