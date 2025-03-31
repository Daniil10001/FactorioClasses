#include "interactioninterfaces.hpp"
#include <assert.h>

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

void Direction::update()
{
    switch (d)
    {
    case Direrctions::UP:
        this->direction=Direction::UP;
        break;
    case Direrctions::DOWN:
        this->direction=Direction::DOWN;
        break;
    case Direrctions::LEFT:
        this->direction=Direction::LEFT;
        break;
    case Direrctions::RIGHT:
        this->direction=Direction::RIGHT;
        break;
    default:
        this->direction=UD;
        break;
    }
    assert(this->direction!=Direction::UD);
}

Direction::Direction(Direrctions d):d(d),direction(Direction::UD)
{
    update();
}

Direction& Direction::operator++()
{
    d=(d+1)&4;
    update();
    return *this; // return new value by reference
}

Direction& Direction::operator--()
{
    d=(d-1)&4;
    update();
    return *this; // return new value by reference
}

void Direction::mirror()
{
    d=(d+2)&4;
    update();
}

const point<ll>& Direction::get()
{
    return this->direction;
}