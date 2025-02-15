#include "material.hpp"

ActionResult operator+(Material& lhs, Material& rhs){
        if (lhs.id!=rhs.id) return ActionResult::BAD;
        unsigned q=min(lhs.capacity-lhs.quantity,rhs.quantity);
        lhs.quantity+=q;
        rhs.quantity-=q;
        return ActionResult::OK;
}

Material& Material::operator+=(const int rhs){
    if (rhs<0) return (*this)-=(-rhs);
    this->quantity+=min(this->capacity-this->quantity,(unsigned)rhs);
    return *this;
};

Material& Material::operator-=(const int rhs){
    if (rhs<=0) return (*this)+=(-rhs);
    this->quantity-=min(this->quantity,(unsigned)rhs);
    return *this;
};

unsigned Material::getId() {
    return this->id;
}

unsigned Material::get_quantity()
{
    return this->quantity;
}

bool Material::isFull() {
    return this->capacity==this->quantity;
}

ActionResult Material::ChangeId(unsigned id)
{
    if (this->quantity!=0) return ActionResult::BAD;
    this->id=id;
    return ActionResult::OK;
}