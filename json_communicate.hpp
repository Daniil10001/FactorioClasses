//
// Created by  Владимир Малахов on 14.02.2025.
//

#ifndef FACTORIO_JSON_COMMUNICATE__
#define FACTORIO_JSON_COMMUNICATE__
#define ll long long
#include "interactioninterfaces.hpp"

class json_communicate {
public:
    json_communicate();
    ~json_communicate();

    static MaterialList* getRequirmentsById(int id);
    static ll getCraftTimeById(int id);
};


#endif //FACTORIO_JSON_COMMUNICATE_H
