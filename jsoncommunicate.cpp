//
// Created by  Владимир Малахов on 14.02.2025.
//

#include "jsoncommunicate.hpp"
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include <iostream>


std::vector<loadingUnit> json_handling::items={};

Document* json_handling::loadJsonDocument(std::string filepath) {
    //using namespace std;

    // if already loaded
    auto temp = findByPath(filepath);
    if (temp != -1)
        return (items.begin() + temp)->getFileInstance();

    std::ifstream file(filepath);
    if(!file)
    {
        std::cout<<"bad read"<<std::endl;
    }
    std::string json((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    Document* doc = new Document;

    doc->Parse(json.c_str());

    if (doc->HasParseError()) {
        std::cerr << "Error parsing JSON: "
             << doc->GetParseError() << std::endl;
        throw "Error parsing: " + filepath;
    }

    items.emplace_back(filepath, true, doc);
    return doc;

}

int json_handling::findByPath(std::string targetpath) {
    for (unsigned i = 0; i < items.size(); i++)
        if (items[i].getPath() == targetpath)
            return i;

    return -1;
}

void json_handling::checkItemsIntegrity()
{
    for (unsigned i = 0; i < items.size(); i++)
        if (items[i].getPath() == "" || items[i].getFileInstance() == nullptr ||
                !items[i].isLoaded())
            throw "File in-memory storing failure: " + items[i].getPath();

}

void json_handling::closeJsonDocument(std::string filepath)
{
    int target = findByPath(filepath);

    if (target == -1) return;

    items.erase(items.begin() + target);

}



//MaterialList* json_communicate::getRequirementsById(int id)
//{
//    MaterialList* ml;
//    switch (id)
//    {
//    case 1001:
//        ml=new MaterialList(3);
//        ml->ids[0]=0;
//        ml->ids[1]=0;
//        ml->ids[2]=1;
//        ml->consumes[0]=0;
//        ml->consumes[1]=0;
//        ml->consumes[2]=-1;
//        break;
//
//    default:
//        nullptr;
//        break;
//    }
//    return ml;
//}

std::string json_communicate::getUrlById(unsigned id) {
    auto itemsDoc = json_handling::getJsonDocument("./resources/config/items.json");
    return (std::string)(*itemsDoc)["items"][id]["url"].GetString();
}


MaterialList* json_communicate::getRequirementsById(unsigned id, unsigned recipe_id) {
    auto prodLists = json_handling::getJsonDocument(
            "./resources/config/items/" + json_communicate::getUrlById(id) + "production.json"
            );

    unsigned count = (*prodLists)["recipes"][recipe_id]["count"].GetInt();

    auto reqList = new MaterialList(count);
    reqList->time = (*prodLists)["recipes"][recipe_id]["time"].GetFloat();

    for (unsigned i = 0; i < count; i++) {
        reqList->consumes[i] = (*prodLists)["recipes"][recipe_id]["consumes"][i].GetInt();
        reqList->ids[i] = (unsigned)(*prodLists)["recipes"][recipe_id]["requirements"][i].GetInt();
    }

    return reqList;
}

std::string json_communicate::getNameById(unsigned id) {
    return (*json_handling::getJsonDocument(

            "./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"

            ))["name"].GetString();
}

