#include "material.hpp"

ActionResult operator+(Material& lhs, Material& rhs){
        if (lhs.id!=rhs.id) return ActionResult::BAD;
        unsigned q=min(lhs.capacity-lhs.quantity,rhs.quantity);
        lhs.quantity+=q;
        rhs.quantity-=q;
        return ActionResult::OK;
}

Material& Material::operator+=(const unsigned& rhs){
    this->quantity+=min(this->capacity-this->quantity,rhs);
    return *this;
};

Material& Material::operator-=(const unsigned& rhs){
    this->quantity-=min(this->quantity,rhs);
    return *this;
};

unsigned Material::getId() {
    return this->id;
}

unsigned Material::get_quantity()
{
    return this->quantity;
}