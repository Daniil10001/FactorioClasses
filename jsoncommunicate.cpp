//
// Created by  Владимир Малахов on 14.02.2025.
//

#include "jsoncommunicate.hpp"


MaterialList* json_communicate::getRequirmentsById(int id)
{
    MaterialList* ml;
    switch (id)
    {
    case 1001:
        ml=new MaterialList(3);
        ml->ids[0]=0;
        ml->ids[1]=0;
        ml->ids[2]=1;
        ml->consumes[0]=0;
        ml->consumes[0]=0;
        ml->consumes[0]=-1;
        break;
    
    default:
        nullptr;
        break;
    }
    return ml;
}