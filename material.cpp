void Material::changeQuantity(int dQ) {
    this->quantity += dQ
}



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

    virtual void getQuantity() = 0;

    virtual void getInfo() = 0;

    virtual void getId() = 0;


};
#endif