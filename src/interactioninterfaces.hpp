#ifndef interactioninterfaces_hpp__
#define interactioninterfaces_hpp__

#include<cstdint>
#include<stdexcept>
#include<cassert>
#include<map>
#define ll long long


class Object;
class Building;
class Factory;
class Dummy;
class Inserter;
class Conveyer;
class Chest;

namespace Types_nps{
enum Types{
    Object,
    Building,
    Dummy,
    Factory,
    Inserter,
    Conveyer,
    Chest,
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
    static inline const point<ll> DOWN=point<ll>(0,1);
    static inline const point<ll> UP=point<ll>(0,-1);
    static inline const point<ll> LEFT=point<ll>(-1,0);
    static inline const point<ll> RIGHT=point<ll>(1,0);
    static inline const point<ll> UD=point<ll>(0,0);
    Direction(Directions d);
    Direction& operator++();
    Direction& operator--();
    void mirror();
    Direction mirrored();
    const point<ll>& get();
    inline Directions dir(){return (Directions)this->d;}
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

template<class T=uint32_t>
class ID
{
    public:
    T id;
    constexpr ID(T id):id(id){}
    ID(ID &id):id(id.id){}
    ID(const ID& id):id(id.id){}
    ID():id(0){}
    inline ID& operator=(ID id){this->id=id.id;return *this;}
    inline ID& operator=(T id){this->id=id;return *this;}
    //inline constexpr friend bool operator==(const ID<> lhs,const ID<> rhs){return (!(lhs.id==0 && rhs.id==0))&&(lhs.id==rhs.id);}
    inline constexpr friend bool operator==(const ID<>& lhs,const ID<>& rhs){return (lhs.id==0 || rhs.id==0)^(lhs.id==rhs.id);}
    inline constexpr friend bool operator>=(const ID<>& lhs,const ID<>& rhs){return (!(lhs.id==0 || rhs.id==0))&&(lhs.id==rhs.id);}
    //inline constexpr friend bool operator!=(const ID<> lhs,const ID<> rhs){return !(lhs==rhs);}
    inline constexpr friend bool operator!=(const ID<>& lhs,const ID<>& rhs){return !(lhs==rhs);}

    inline constexpr friend bool operator==(const ID<>& lhs,T rhs){assert(rhs==0); return lhs.id==0;}

};



class MaterialList
{
private:
public:
    unsigned count;
    ID<> *ids;
    int *consumes;
    std::string name;
    float time; // may be crafting time
    MaterialList();
    MaterialList(unsigned count);
    MaterialList(MaterialList&);
    ~MaterialList();
};

template<class T>
constexpr const T& min(const T& a, const T& b){    return (b < a) ? b : a;    }

template<class T>
constexpr const T& max(const T& a, const T& b){    return (b > a) ? b : a;    }

#endif