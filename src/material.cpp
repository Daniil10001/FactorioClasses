#include "material.hpp"
#include <stdexcept>


ActionResult operator+(Material& lhs, Material& rhs){
        if (lhs.id == 0 && rhs.id==0)   throw std::invalid_argument("Can not add nothing to nothing");
        if (rhs.id == 0) throw std::invalid_argument("Can not add nothing to something");;
        if (lhs.id == 0)    lhs.ChangeId(rhs.id);
        //std::cout<<'\n'<<"|id "<<lhs.id.id<<' '<<rhs.id.id<<'|';
        if (lhs.id!=rhs.id) return ActionResult::BAD;
        unsigned q=min(lhs.capacity-lhs.quantity,rhs.quantity);
        lhs.quantity+=q;
        rhs.quantity-=q;
        return ActionResult::OK;
}

Material& Material::operator+=(const int rhs){
    if (rhs<0) return (*this)-=(-rhs);
    if (this-> id==0) throw std::invalid_argument("Can not add nothing to nothing");
    this->quantity+=min(this->capacity-this->quantity,(unsigned)rhs);
    return *this;
}

Material& Material::operator-=(const int rhs){
    if (rhs<0) return (*this)+=(-rhs);
    if (this-> id==0) throw std::invalid_argument("Can not add nothing to nothing");
    this->quantity-=min(this->quantity,(unsigned)rhs);
    return *this;
}

ActionResult Material::ChangeId(ID<> id)
{
    if (this->quantity!=0) return ActionResult::BAD;
    this->id=id;
    return ActionResult::OK;
}