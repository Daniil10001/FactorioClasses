
#include"object.hpp"
#include "jsoncommunicate.hpp"

Object::Object(ll x,ll y, unsigned x_size, unsigned y_size)
{
    this->initilised=true;
    this->size.x=x_size;
    this->size.y=y_size;
    set_cord(x,y);
}

Object::Object(unsigned id)
{                   //dummy thin neded to replaced by json
    this->size.x=2;
    this->size.y=2;
    this->initilised=true;
};

void Object::set_cord(ll x,ll y)
{
    this->initilised=true;
    this->p.x=x;
    this->p.y=y;
}

point<ll> Object::get_cord()
{
    return this->p;
}

point<unsigned> Object::get_size()
{
    return this->size;
}

Object::~Object()
{
    
}