#ifndef interactioninterfaces_hpp__
#define interactioninterfaces_hpp__

template<typename T> class point
{
    public:
    T x,y;
    point(T x, T y):x(x),y(y){};
    point():x(0),y(0){};
    void set(T x,T y){
        this->x=x;
        this->y=y;
    }
};

enum class State
{
    OK,
    NotEnoughMaterial,
    Busy,
    Full,
};

enum ActionResult
{
    OK,
    BAD,
};

enum Connections
{
    Standart,
    Chain
};

class MaterialList
{
private:
public:
    unsigned count;
    unsigned *ids;
    int *consumes;
    MaterialList();
    MaterialList(int count);
    ~MaterialList();
};

template<class T>
const T& min(const T& a, const T& b){    return (b < a) ? b : a;    }

template<class T>
const T& max(const T& a, const T& b){    return (b > a) ? b : a;    }

#endif