#ifndef matterial_hpp__
#define matterial_hpp__

#include "interactioninterfaces.hpp"

class Material {
protected:
    unsigned quantity;
    unsigned capacity =64;
    ID<> id;
public:
    Material():quantity(0),id(0){};
    Material(unsigned quantity, unsigned id=0) {
        this->quantity = quantity;
        this->id=id;
    }
    Material(unsigned quantity, ID<> id=0) {
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

    ActionResult ChangeId(ID<> id);

    inline ID<> getId() const {return this->id;}

    inline unsigned get_quantity() const {return this->quantity;}
    
    inline unsigned get_maxquantity() const {return this->capacity;}
    
    inline bool isFull() const {return this->capacity==this->quantity;}    

    void getInfo() const;

};
#endif