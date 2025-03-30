
#include"object.hpp"
#include "jsoncommunicate.hpp"

constexpr const char xs[]="size_x";
constexpr const char ys[]="size_y";

Object::Object(ll x,ll y, unsigned x_size, unsigned y_size):p(x,y),size(x_size,y_size)
{
    this->initilised=true;
}

Object::Object(unsigned id)
{                   //dummy thin neded to replaced by json
    this->size.x=json_communicate::get_property<unsigned,Object,Checking::size_a(xs),xs>(id);
    this->size.x=json_communicate::get_property<unsigned,Object,Checking::size_a(ys),ys>(id);
    this->initilised=true;
};

void Object::set_cord(ll x,ll y)
{
    this->p.set(x,y);
    this->initilised=true;
}

const point<ll>& Object::get_cord()
{
    return this->p;
}

const point<unsigned>& Object::get_size()
{
    return this->size;
}

Object::~Object()
{
    
}