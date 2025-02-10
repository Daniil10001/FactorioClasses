#ifndef matterial_hpp__
#define matterial_hpp__

class Material {
protected:
    int quantity;
    int id;
public:
    Material(int quantity) {
        this->quantity = quantity;
        this->id=0;
    }

    virtual void changeQuantity() = 0;

    virtual int getQuantity() = 0;

    virtual void getInfo() = 0;

    virtual int getId() = 0;


};
#endif