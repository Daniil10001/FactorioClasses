#ifndef matterial_hpp__
#define matterial_hpp__

#include "interactioninterfaces.hpp"

class Material {
protected:
    unsigned quantity;
    unsigned capacity =64;
    unsigned id;
public:
    Material():quantity(0),id(0){};
    Material(unsigned quantity, unsigned id=0) {
        this->quantity = quantity;
        this->id=id;
    }

    /*
        Rules of adding it is working like move
        first if where it added and second is what added to first
        for subtraction it is similar
        return OK if same id and bad otherwise
    */
    friend ActionResult operator+(Material& lhs, Material& rhs);

    Material& operator+=(const int rhs);

    Material& operator-=(const int rhs);

    ActionResult ChangeId(unsigned id);

    unsigned get_quantity() const;

    unsigned get_maxquantity() const;

    bool isFull() const;

    void getInfo() const;

    unsigned getId() const;

};
#endif