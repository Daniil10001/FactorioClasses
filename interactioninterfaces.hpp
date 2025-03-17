#ifndef interactioninterfaces_hpp__
#define interactioninterfaces_hpp__

template<typename T> struct point
{
    T x,y;
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