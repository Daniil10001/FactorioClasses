#ifndef building_hpp__
#define building_hpp__

#include"object.hpp"
#include"material.hpp"

class building: public Object
{
private:
    int id;
    
public:
    building(ll x,ll y, int id);

};


#endif