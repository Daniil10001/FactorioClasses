
#include"object.hpp"

Object::Object()
{
    this->initilised=false;
}

Object::Object(ll x,ll y)
{
    this->initilised=false;
    set_cord(x,y);
}

void Object::set_cord(ll x,ll y)
{
    this->p.x=x;
    this->p.y=y;
}

point Object::get_cord()
{
    return this->p;
}