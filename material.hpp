#ifndef matterial_hpp__
#define matterial_hpp__

#include "interactioninterfaces.hpp"


class Material {
protected:
    unsigned quantity;
    const unsigned capicy =64;
    unsigned id;
public:
    Material(unsigned quantity) {
        this->quantity = quantity;
        this->id=0;
    }
    /*
        Rules of adding it is working like move
        first if where it added and second is what added to first
        for subtraction it is similar
        return OK if same id and bad otherwise
    */
    friend ActionResult operator+(Material& lhs, Material& rhs);

    Material& operator+=(const unsigned& rhs);

    Material& operator-=(const unsigned& rhs);

    virtual void getInfo() = 0;

    virtual unsigned getId() = 0;


};
#endif