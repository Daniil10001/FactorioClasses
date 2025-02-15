#include "interactioninterfaces.hpp"

MaterialList::MaterialList()
{
    this->count=0;
}

MaterialList::MaterialList(int count)
{
    this->count=count;
    this->ids=new unsigned[count];
    this->consumes=new int[count];
}

MaterialList::~MaterialList()
{
    delete [] ids;
    delete [] consumes;
}