#ifndef objectparametrshandler_hpp__
#define objectparametrshandler_hpp__

#include <cstdint>
#include<array>
#include <cstdlib>
#include <typeinfo>
#include "interactioninterfaces.hpp"

namespace Checking
{

template<typename A, typename B>
struct pair{
    A first;
    B second;

    constexpr pair<A, B>& operator=(const pair<A, B>& r)
    {
        this->first=r.first;
        this->second=r.second;
        return *this;
    }
};

struct sarr
{
    const static std::size_t prop_c=10,lenght=20;
    char d[prop_c][lenght];

    constexpr sarr& operator=(const sarr& r)
    {
        for (unsigned i=0;i<this->prop_c;i++)
            for (unsigned j=0;j<this->lenght;j++)
                (this->d)[i][j]=r.d[i][j];
        return *this;
    };
    constexpr sarr& operator=(sarr& r)
    {
        for (unsigned i=0;i<this->prop_c;i++)
            for (unsigned j=0;j<this->lenght;j++)
                (this->d)[i][j]=r.d[i][j];
        return *this;
    };

};

template<class T>
constexpr Types type_id(){
    if (std::is_same<T,Object>())
        return Types::Object;
    if (std::is_same<T,Building>())
        return Types::Building;
    if (std::is_same<T,Factory>())
        return Types::Factory;
    throw "Not defined type";
    return  Types::Count;
}

template <typename  Key, typename Value, std::size_t Size>
class Map {
    private:
    const std::array<pair<Key, Value>, Size> data;
    public:
    const std::size_t size;
    constexpr Map(std::array<pair<Key, Value>, Size> data):data(data),size(Size) {}

    

  [[nodiscard]] constexpr const Value* at_index(const std::size_t &key) const {
    if (key < Size) {
      return &(data.at(key).second);
    } else {
      throw "Not Found element" ;
    }
  }

  [[nodiscard]] constexpr const Value* at_index(std::size_t &key) const {
    if (key < Size) {
      return &(data.at(key).second);
    } else {
      throw "Not Found element" ;
    }
  }

  [[nodiscard]] constexpr std::size_t find(Key &key) const {
    auto it = data.begin(); 
    for (;it!=data.end();it++)
        if (it->first == key)
            break;
    return it-data.begin();
  }

  [[nodiscard]] constexpr const Value* at(Key &key) const {return this->at_index(this->find(key));}

};

template<typename T, std::size_t N>
constexpr unsigned size_a(T (&a)[N])
{
    return (sizeof a)/(sizeof *a);
}

template<std::size_t N1, std::size_t N2>
class Carrier
{
private:
    const Map<Types,sarr,N1> prop;
    const Map<Types,Types, N2> nasl;
public:
    constexpr Carrier(Map<Types,sarr,N1> p, Map<Types,Types, N2> n):prop(p), nasl(n){};

    template<class T, const std::size_t N>
    constexpr bool check(const char (&C)[N]) const
    {
        if (sarr::lenght<N) throw "Too long property";
        bool b=0;
        Types Tt = type_id<T>();
        size_t it=nasl.find(Tt);
        for (;;)
        {
            if(prop.find(Tt)!=N1)
            {
                const sarr* sr=prop.at(Tt);
                for (unsigned i=0;i<sarr::prop_c;i++)
                {
                    b=0;
                    for (std::size_t s=0;s<min(sarr::lenght,N);s++)
                     if (sr->d[i][s]!=C[s])
                        {
                            b=1;
                            break;
                     }
                if (!b) return true;
                }
            }
            if (it==N2) break;
            Tt=*nasl.at_index(it);
            it=nasl.find(Tt);
        }
        return false;
    }

    template<Types T, const std::size_t N>
    constexpr bool check(const char (&C)[N]) const
    {
        if (sarr::lenght<N) throw "Too long property";
        bool b=0;
        Types Tt = T;
        size_t it=nasl.find(Tt);
        for (;;)
        {
            if(prop.find(Tt)!=N1)
            {
                const sarr* sr=prop.at(Tt);
                for (unsigned i=0;i<sarr::prop_c;i++)
                {
                    b=0;
                    for (std::size_t s=0;s<min(sarr::lenght,N);s++)
                     if (sr->d[i][s]!=C[s])
                        {
                            b=1;
                            break;
                     }
                if (!b) return true;
                }
            }
            if (it==N2) break;
            Tt=*nasl.at_index(it);
            it=nasl.find(Tt);
        }
        return false;
    }
};


template<typename Types, std::size_t N1, std::size_t N2>
constexpr Carrier<N1, N2> make_carrier(const pair<Types,sarr> (&cup)[N1], const pair<Types, Types> (&ns)[N2])
{
    std::array<pair<Types,sarr>,N1> cupa={};
    std::array<pair<Types, Types>,N2> nsa={};
    for (std::size_t i=0;i<N1;i++) cupa[i]=cup[i];
    for (std::size_t i=0;i<N2;i++) nsa[i]=ns[i];
    return Carrier<N1,N2>(cupa,nsa);
}


static constexpr inline pair<Types,sarr> const cup[]={{Types::Object, {"size_x","size_y","image"}},{Types::Factory,{"level","cooldown"}}}; //возможные параметры объекта

//связь наслелования элемент 1 - потомок, 2 - предок, поддерживаются только деревья с одним предком у каждой вершины
static constexpr inline pair<Types, Types> const ns[]={{Types::Building,Types::Object}, {Types::Factory,Types::Building}}; 

static constexpr inline auto Propeties=make_carrier(cup,ns);
}

static_assert(Checking::Propeties.check<Factory>("size_x"));
static_assert(!Checking::Propeties.check<Factory>("point"));

#endif