
#include"object.hpp"

Object::Object(ll x,ll y, unsigned x_size, unsigned y_size)
{
    this->initilised=false;
    this->size.x=x_size;
    this->size.y=y_size;
    set_cord(x,y);
}

void Object::set_cord(ll x,ll y)
{
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