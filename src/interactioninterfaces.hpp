#ifndef interactioninterfaces_hpp__
#define interactioninterfaces_hpp__

#define ll long long

class Object;
class Building;
class Factory;
class Dummy;
class Inserter;

namespace Types_nps{
enum Types{
    Object,
    Building,
    Dummy,
    Factory,
    Count,
};
}

using Types_nps::Types;


template<typename T> class point
{
    public:
    T x,y;
    point(T x, T y):x(x),y(y){};
    point():x(0),y(0){};
    inline void set(T x,T y){
        this->x=x;
        this->y=y;
    }
    inline point& operator+=(point& rhs) 
    {
        this->x+=rhs.x;
        this->y+=rhs.y;          
        return *this;
    }

    inline point& operator-=(point& rhs) 
    {
        this->x-=rhs.x;
        this->y-=rhs.y;          
        return *this;
    }
    friend inline point operator+(point lhs, point rhs)
    {
        lhs += rhs; 
        return lhs;
    }

    friend inline point operator-(point lhs, point rhs)
    {
        lhs -= rhs; 
        return lhs;
    }

    friend inline bool operator==(point l, point r)
    {
        if (l.x==r.x && l.y==r.y) return 1;
        return 0;
    }

    friend inline bool operator!=(point l, point r)
    {
        return !(l==r);
    }
};

enum Directions: short
    {
        RIGHT,
        UP,
        LEFT,
        DOWN
};

class Direction 
{
    private:
    short d;
    point<ll> direction;
    void update();
    public:
    static inline const point<ll> DOWN=point<ll>(0,-1);
    static inline const point<ll> UP=point<ll>(0,1);
    static inline const point<ll> LEFT=point<ll>(-1,0);
    static inline const point<ll> RIGHT=point<ll>(1,0);
    static inline const point<ll> UD=point<ll>(0,0);
    Direction(Directions d);
    Direction& operator++();
    Direction& operator--();
    void mirror();
    const point<ll>& get();
};

namespace States_nps{
enum class State: short
{
    OK,
    NotEnoughMaterial,
    Busy,
    Full,
};
};
using States_nps::State;

namespace ActionResult_nps{
enum ActionResult: short
{
    OK,
    BAD,
};
};
using ActionResult_nps::ActionResult;

namespace Connections_nps{
enum Connections: short
{
    Standart,// base do not remove
    Chain,
    Count // Duumy element to count connection types
};
};
using Connections_nps::Connections;


class MaterialList
{
private:
public:
    unsigned count;
    unsigned *ids;
    int *consumes;
    float time; // may be crafting time
    MaterialList();
    MaterialList(unsigned count);
    ~MaterialList();
};

template<class T>
constexpr const T& min(const T& a, const T& b){    return (b < a) ? b : a;    }

template<class T>
constexpr const T& max(const T& a, const T& b){    return (b > a) ? b : a;    }

#endif