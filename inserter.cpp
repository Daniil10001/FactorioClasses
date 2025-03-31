#include"inserter.hpp"

ActionResult inserter::put_material(Material *m)
{
    return ActionResult::BAD;
}

Material* inserter::get_material(unsigned cell)
{
    return nullptr;
}

ActionResult inserter::set_cellfrom(unsigned cell)
{
    for (Building* const cn :con.GetConnectionsFrom())
    {
        if (cn->get_requirments()->count<=cell)
            return ActionResult::BAD;
    }
    this->cellfrom=cell;
    return ActionResult::OK;
}