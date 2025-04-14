#ifndef sessionlogic_hpp__
#define sessionlogic_hpp__


#include "factory.hpp"
#include <array>
#include <set>
#include <map>
#include <chrono>

enum ObjectTypes
{
    Map,
    Buildings,
    SpecialPoints,
    Count
};

class TimersHandler
{
    private:
        std::map<Object*,std::chrono::time_point<std::chrono::system_clock>> Timers;

    public:

    double get_delta_s(Object* o)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-Timers[o]).count()/1e6;
    }

    void restart_timer(Object* o)
    {
        Timers[o]=std::chrono::system_clock::now();
    }

    ActionResult register_timer(Object* o)
    {
        Timers.emplace(std::make_pair(o,std::chrono::system_clock::now()));
    }

    ActionResult unregister_timer(Object* o)
    {
        Timers.erase(o);
    }
};

class SessionHandler
{
    private:
    std::array<std::set<Object*>,ObjectTypes::Count> objs;
    std::map<Object *,std::vector<std::pair<point<ll>,std::pair<bool,Object*>>>> interesting_points;
    TimersHandler tims;
    public:
    SessionHandler()
    {
        objs[ObjectTypes::Map].emplace(new Object(100,100));
        objs[ObjectTypes::Buildings].emplace(new Object(1,2));
        objs[ObjectTypes::Buildings].emplace(new Factory(1001u,point<ll>(1,1),Directions::UP));
    };

    std::set<Object *> const get_layer(ObjectTypes lr) const;

    template<Types T>
    ActionResult addToLayerB(unsigned id, point<ll> p, Direction dir);

    ActionResult delFromLayerB(Object * obj);

    ActionResult delFromLayerB(Object * const obj);

    ~SessionHandler(){};
};




#endif