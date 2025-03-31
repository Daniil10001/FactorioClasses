#ifndef sessionlogic_hpp__
#define sessionlogic_hpp__

#include "object.hpp"
#include <array>
#include <set>
#include <map>
#include <chrono>

enum ObjectTypes
{
    Map,
    Buildings,
    Resources,
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

    ActionResult register_timer(Object* o)
    {
        Timers.erase(o);
    }
};

class SessionHandler
{
    public:
    std::array<std::set<Object*>,ObjectTypes::Count> obj;
    TimersHandler tims;
};

#endif