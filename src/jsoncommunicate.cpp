//
// Created by  Владимир Малахов on 14.02.2025.
//

#include "jsoncommunicate.hpp"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/encodings.h>

#include <iostream>
#include <fstream>


std::vector<loadingUnit> json_handling::items={};

std::map<unsigned, std::shared_ptr<sf::Texture>> texture_handler::textures;

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
    throw std::runtime_error("File in-memory storing failure: " + items[i].getPath());
}

void json_handling::closeJsonDocument(std::string filepath)
{
    int target = findByPath(filepath);

    if (target == -1) return;

    items.erase(items.begin() + target);

}





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
    throw std::runtime_error((std::string)"Not found '"+ c + "' in "+std::to_string(id));
}

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
    throw std::runtime_error((std::string)"Not found '"+ c + "' in "+std::to_string(id));
}

template<class T,bool B>
inline typename std::enable_if<std::is_same<T, float>::value, T>::type
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
    throw std::runtime_error((std::string)"Not found '"+ c + "' in "+std::to_string(id));
}

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
    throw std::runtime_error((std::string)"Not found '"+ c + "' in "+std::to_string(id));
}

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
    throw std::runtime_error((std::string)"Not found '"+ c + "' in "+std::to_string(id));
}


std::string json_communicate::getUrlById(unsigned id) {
    auto itemsDoc = json_handling::getJsonDocument("./resources/config/items.json");
    return getValueById<std::string>((*itemsDoc)["items"].GetArray(),id,"url");
}

MaterialList* json_communicate::getRequirementsById(unsigned id, unsigned recipe_id) {
    auto prodLists = json_handling::getJsonDocument(
            "./resources/config/items/" + json_communicate::getUrlById(id) + "production.json"
            );
    auto arr=(*prodLists)["recipes"].GetArray();

    unsigned count = getValueById<unsigned>(arr,recipe_id,"count");;

    auto reqList = new MaterialList(count);
    reqList->time = getValueById<float>(arr,recipe_id,"time");

    auto cons=getValueById<rapidjson::GenericArray<true,rapidjson::Value>>(arr,recipe_id,"consumes");
    auto req=getValueById<rapidjson::GenericArray<true,rapidjson::Value>>(arr,recipe_id,"requirements");

    for (unsigned i = 0; i < count; i++) {
        reqList->consumes[i] = cons[i].GetInt();
        reqList->ids[i] = req[i].GetUint();
    }

    return reqList;
}

std::string json_communicate::getNameById(unsigned id) {
    return (*json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"))["name"].GetString();
}

sf::Texture& json_communicate::getTextureById (unsigned id) {
    if (texture_handler::textures.count(id)) return *texture_handler::textures.at(id);
    auto ihandler = json_handling::getJsonDocument( // it's revolution, johny
        "./resources/config/items/" + json_communicate::getUrlById(id) + "main.json");
    std::string path="./resources/includes/"+json_communicate::getUrlById(id)+(std::string)((*ihandler)["image"].GetString());
    std::shared_ptr<sf::Texture> texteure(new sf::Texture(path));
    texture_handler::textures.emplace(id,texteure);
    return *texteure;
}

