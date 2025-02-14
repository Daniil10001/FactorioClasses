#ifndef interactioninterfaces_hpp__
#define interactioninterfaces_hpp__

enum State
{
    OK,
    NotEnoughMaterial,
    Busy,
};

enum ActionResult
{
    OK,
    BAD,
};

class MaterialList
{
private:
public:
    int count;
    int *ids;
    MaterialList();
    MaterialList(int count);
    ~MaterialList();
};

MaterialList::MaterialList()
{
    this->count=0;
}

MaterialList::MaterialList(int count)
{
    this->count=count;
    this->ids=new int[count];
}

MaterialList::~MaterialList()
{
    delete [] ids;
}

#endif