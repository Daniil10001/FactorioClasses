#ifndef sessionlogic_hpp__
#define sessionlogic_hpp__

#include "factory.hpp"
#include "inserter.hpp"
#include "conveyer.hpp"
#include "jsoncommunicate.hpp"
#include <array>
#include <set>
#include <functional>
#include <atomic>
#include <map>
#include <vector>
#include <chrono>
#include <stdexcept>

enum ObjectTypes
{
    Map,
    Buildings,
    SpecialPoints,
    Count
};

class RunMachine
{
public:
    enum StatesOfObj : short
    {
        Wait,
        Action,
        ActionMove,
        Count
    };

private:
    short _curr;
    std::array<std::function<ActionResult()>, StatesOfObj::Count> func_call;

public:
    RunMachine(Building *obj);
    void Do();
    inline short getCurr() { return _curr; };
};

class TimersHandler
{
private:
    std::map<Building *, std::chrono::time_point<std::chrono::system_clock>> Timers;
    std::map<Building *, RunMachine *> Runner;
    bool doing = false;
    bool busy = false;

    double get_delta_s(Building *o)
    {
        if (Timers.count(o) == 0)
            throw std::invalid_argument("No timer for object");
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - Timers[o]).count() / 1e6;
    }

    void restart_timer(Building *o)
    {
        if (Timers.count(o) == 0)
            throw std::invalid_argument("No timer for object");
        Timers[o] = std::chrono::system_clock::now();
    }

public:
    int active = 0;
    void startHandling(bool onetime = false);
    ~TimersHandler();

    ActionResult register_timer(Object *o)
    {
        if (!dynamic_cast<Building *>(o))
            throw std::invalid_argument("Not a building added!");
        while (doing || busy)
        {
        }
        busy = true;
        Building *b = dynamic_cast<Building *>(o);
        Timers.emplace(std::make_pair(b, std::chrono::system_clock::now()));
        Runner.emplace(std::make_pair(b, new RunMachine(b)));
        busy = false;
        return ActionResult::OK;
    }

    ActionResult unregister_timer(Object *o)
    {
        if (!dynamic_cast<Building *>(o))
            throw std::invalid_argument("Not a building unregistering!");
        while (doing || busy)
        {
        }
        doing = true;
        Building *b = dynamic_cast<Building *>(o);
        if (Timers.count(b) != 0)
        {
            Timers.erase(b);
            delete Runner[b];
            Runner.erase(b);
            busy = false;
        }
        else
        {
            std::cerr<<"can not remove obj!";
            busy = false;
            return ActionResult::BAD;
        }
        busy = false;
        return ActionResult::OK;
    }
};

class SessionHandler
{
private:
    std::array<std::set<Object *>, ObjectTypes::Count> objs;
    // std::map<Object *,Dummy *> interesting_points;
    TimersHandler tims;

    void MakeConnections(Object *b);
    void ClearDummies(const std::set<Object *> &setobj);
    Object *findObj(point<ll> p, ObjectTypes layer);

public:
    SessionHandler() {
        // objs[ObjectTypes::Map].emplace(new Object(100,100));
        // objs[ObjectTypes::Buildings].emplace(new Object(1,2));
        // objs[ObjectTypes::Buildings].emplace(new Factory(1001u,point<ll>(1,1),Directions::UP));
    };

    ~SessionHandler();

    std::set<Object *> findInters(point<ll> p, point<unsigned> sz, ObjectTypes layer);

    std::set<Object *> const get_layer(ObjectTypes lr) const;

    Object *addToLayerB(unsigned id, point<ll> p, Direction dir);

    const std::vector<Material> getBuildingInventory(Object *) const;

    ActionResult delFromLayerB(Object *obj);

    TimersHandler &getTims()
    {
        return tims;
    }
};

#endif