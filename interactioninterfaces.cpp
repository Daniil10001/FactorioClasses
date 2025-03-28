#include "interactioninterfaces.hpp"

MaterialList::MaterialList()
{
    this->count=0;
}

MaterialList::MaterialList(unsigned count)
{
    this->count=count;
    this->time = 0;
    this->ids=new unsigned[count];
    this->consumes=new int[count];
}

MaterialList::~MaterialList()
{
    delete [] ids;
    delete [] consumes;
}