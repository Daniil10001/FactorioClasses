#ifndef inserter_hpp__
#define inserter_hpp__
#include "building.hpp"

class inserter: public Building
{
protected:
    unsigned id;
    Connection con;
    unsigned cellfrom;
public:
    inserter(unsigned int level, unsigned id, point<ll> position);
    
    ActionResult put_material(Material *m) final;
    Material* get_material(unsigned cell) final;

    ~inserter();

    ActionResult set_cellfrom(unsigned cell);
};


#endif