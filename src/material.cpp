#include "material.hpp"

ActionResult operator+(Material& lhs, Material& rhs){
        if (lhs.id == 0 && rhs.id==0)   return ActionResult::BAD;
        if (lhs.id == 0)    lhs.ChangeId(rhs.id);
        if (lhs.id!=rhs.id) return ActionResult::BAD;
        unsigned q=min(lhs.capacity-lhs.quantity,rhs.quantity);
        lhs.quantity+=q;
        rhs.quantity-=q;
        return ActionResult::OK;
}

Material& Material::operator+=(const int rhs){
    if (this-> id==0) throw "Can not add nothing to nothing";
    if (rhs<0) return (*this)-=(-rhs);
    this->quantity+=min(this->capacity-this->quantity,(unsigned)rhs);
    return *this;
}

Material& Material::operator-=(const int rhs){
    if (this-> id==0) throw "Can not add nothing to nothing";
    if (rhs<0) return (*this)+=(-rhs);
    this->quantity-=min(this->quantity,(unsigned)rhs);
    return *this;
}

ActionResult Material::ChangeId(unsigned id)
{
    if (this->quantity!=0) return ActionResult::BAD;
    this->id=id;
    return ActionResult::OK;
}