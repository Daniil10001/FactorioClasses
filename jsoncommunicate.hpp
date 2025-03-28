//
// Created by  Владимир Малахов on 14.02.2025.
//

#ifndef jsoncommunicate_hpp__
#define jsoncommunicate_hpp__
#define ll long long
#include "interactioninterfaces.hpp"
#include "include/rapidjson/document.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace rapidjson;

// storing class for loaded json file
class loadingUnit {
private:
    std::string path;
    bool IsLoaded;
    std::shared_ptr<Document> file;

public:
    loadingUnit(std::string path, bool isLoaded, Document* doc) :
        path(path),IsLoaded(isLoaded), file(doc) {};

    ~loadingUnit() {
        std::cout<<path<<'\n';
        std::cout<<"deleted\n";
    }

    Document* getFileInstance() {
        return file.get();
    }

    std::string getPath() {
        return path;
    }

    bool isLoaded() {
        return IsLoaded;
    }
};

//
class json_handling {
private:
    static std::vector<loadingUnit> items;

public:
    json_handling();
    ~json_handling();

    static Document* loadJsonDocument(std::string filepath);

    static Document* getJsonDocument(std::string filepath) {
        return loadJsonDocument(filepath);
    }

    // returns -1 if target not found
    static int findByPath(std::string targetpath);

    static void closeJsonDocument(std::string filepath);

    // check if any failure loading is present
    static void checkItemsIntegrity();

};

class json_communicate {
public:
    json_communicate();
    ~json_communicate();

    static std::string getNameById(unsigned id);

    static std::string getUrlById(unsigned id);

    // returns first recipe by default
    static MaterialList* getRequirementsById(unsigned id) {
        return getRequirementsById(id, 0);
    }

    static MaterialList* getRequirementsById(unsigned id, unsigned recipe_id);

    static ll getCraftTimeById(unsigned id);


};


#endif //FACTORIO_JSON_COMMUNICATE_H
