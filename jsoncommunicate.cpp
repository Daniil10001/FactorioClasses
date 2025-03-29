//
// Created by  Владимир Малахов on 14.02.2025.
//

#include "jsoncommunicate.hpp"
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/encodings.h"

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



/*MaterialList* json_communicate::getRequirementsById(unsigned id, unsigned recipe_id)
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
       ml->consumes[1]=0;
       ml->consumes[2]=-1;
       break;

   default:
       nullptr;
       break;
   }
   return ml;
}*/

//template<class T, bool B>
//T getValueById(rapidjson::GenericArray<B, rapidjson::Value> arr, unsigned id,std::string c);

template<class T,bool B>
inline typename std::enable_if<std::is_same<T, unsigned>::value, T>::type
getValueById(rapidjson::GenericArray<B, rapidjson::Value> arr,unsigned id,const char *c)
{
    rapidjson::Value::ConstMemberIterator it;
    for (auto elem=arr.begin();elem!=arr.end();elem++)
    {
        it=elem->FindMember("id");
        assert (it!=elem->MemberEnd());
        if ((unsigned)(it->value.GetUint())==id)
        {
            it=elem->FindMember(c);
            assert (it!=elem->MemberEnd());
            return (unsigned)it->value.GetUint();
        }
    }
};

template<class T,bool B>
inline typename std::enable_if<std::is_same<T, int>::value, T>::type
getValueById(rapidjson::GenericArray<B, rapidjson::Value> arr,unsigned id,const char *c)
{
    rapidjson::Value::ConstMemberIterator it;
    for (auto elem=arr.begin();elem!=arr.end();elem++)
    {
        it=elem->FindMember("id");
        assert (it!=elem->MemberEnd());
        if ((unsigned)(it->value.GetUint())==id)
        {
            it=elem->FindMember(c);
            assert (it!=elem->MemberEnd());
            return (int)it->value.GetInt();
        }
    }
};

template<class T,bool B>
inline typename std::enable_if<std::is_same<T, float>::value, float>::type
getValueById(rapidjson::GenericArray<B, rapidjson::Value> arr,unsigned id,const char *c)
{
    rapidjson::Value::ConstMemberIterator it;
    for (auto elem=arr.begin();elem!=arr.end();elem++)
    {
        it=elem->FindMember("id");
        assert (it!=elem->MemberEnd());
        if ((unsigned)(it->value.GetUint())==id)
        {
            it=elem->FindMember(c);
            assert (it!=elem->MemberEnd());
            return (float)it->value.GetFloat();
        }
    }
};

template<class T ,bool B>
inline typename std::enable_if<std::is_same<T, std::string>::value, T>::type
getValueById(rapidjson::GenericArray<B, rapidjson::Value> arr,unsigned id,const char *c)
{
    rapidjson::Value::ConstMemberIterator it;
    for (auto elem=arr.begin();elem!=arr.end();elem++)
    {
        it=elem->FindMember("id");
        assert (it!=elem->MemberEnd());
        if ((unsigned)(it->value.GetUint())==id)
        {
            it=elem->FindMember(c);
            assert (it!=elem->MemberEnd());
            return (std::string)it->value.GetString();
        }
    }
};

template<class T ,bool B>
inline typename std::enable_if<std::is_same<T, rapidjson::GenericArray<true, rapidjson::Value>>::value, T>::type
getValueById(rapidjson::GenericArray<B, rapidjson::Value> arr,unsigned id,const char *c)
{
    rapidjson::Value::ConstMemberIterator it;
    for (auto elem=arr.begin();elem!=arr.end();elem++)
    {
        it=elem->FindMember("id");
        assert (it!=elem->MemberEnd());
        if ((unsigned)(it->value.GetUint())==id)
        {
            it=elem->FindMember(c);
            assert (it!=elem->MemberEnd());
            return (rapidjson::GenericArray<true, rapidjson::Value>)it->value.GetArray();
        }
    }
};

std::string json_communicate::getUrlById(unsigned id) {
    auto itemsDoc = json_handling::getJsonDocument("./resources/config/items.json");
    return getValueById<std::string>((*itemsDoc)["items"].GetArray(),id,"url");
}

MaterialList* json_communicate::getRequirementsById(unsigned id, unsigned recipe_id) {
    auto prodLists = json_handling::getJsonDocument(
            "./resources/config/items/" + json_communicate::getUrlById(id) + "production.json"
            );

    unsigned count = getValueById<unsigned>((*prodLists)["recipes"].GetArray(),recipe_id,"count");;

    auto reqList = new MaterialList(count);
    reqList->time = getValueById<float>((*prodLists)["recipes"].GetArray(),recipe_id,"time");

    auto cons=getValueById<rapidjson::GenericArray<true,rapidjson::Value>>((*prodLists)["recipes"].GetArray(),recipe_id,"consumes");
    auto req=getValueById<rapidjson::GenericArray<true,rapidjson::Value>>((*prodLists)["recipes"].GetArray(),recipe_id,"requirements");

    for (unsigned i = 0; i < count; i++) {
        reqList->consumes[i] = cons[i].GetInt();
        reqList->ids[i] = req[i].GetUint();
    }

    return reqList;
}

std::string json_communicate::getNameById(unsigned id) {
    return (*json_handling::getJsonDocument(

            "./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"

            ))["name"].GetString();
}

