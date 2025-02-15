#ifndef interactioninterfaces_hpp__
#define interactioninterfaces_hpp__

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
    int count;
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