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

std::map<unsigned, std::map<Directions,std::shared_ptr<sf::Texture>>> TextureHandler::textures;

std::map<unsigned, Types> TypesHandler::tps=TypesHandler::generate();

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

std::string json_communicate::getNameById(unsigned id) {
    return (*json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"))["name"].GetString();
}

std::map<unsigned,Types> TypesHandler::generate()
{
    std::map<std::string, Types> String2Type = {{"Factory",Types::Factory},
            {"Inserter",Types::Inserter}, {"Conveyer",Types::Conveyer}, {"Chest",Types::Chest}};
    std::map<unsigned,Types> mp;
    auto itemsDoc = json_handling::getJsonDocument("./resources/config/items.json");
    auto arr=(*itemsDoc)["items"].GetArray();
    rapidjson::Value::ConstMemberIterator iti,itt;
    char buf[128];
    for (auto elem=arr.begin();elem!=arr.end();elem++)
    {
        iti=elem->FindMember("id");
        if (iti==elem->MemberEnd())
        {
            sprintf(buf, "in items.json element with number %i dose not have id field", (unsigned int)(elem-arr.begin()));
            throw std::runtime_error((const char *)buf);
        }
        itt=elem->FindMember("type");
        if (itt==elem->MemberEnd())
        {
            sprintf(buf, "in items.json element with id %i dose not have type field", (unsigned)iti->value.GetUint());
            throw std::runtime_error((const char *)buf);
        }
        if ((std::string)itt->value.GetString() == "Material")
            continue;
        if (String2Type.count((std::string)itt->value.GetString())==0)
            throw std::runtime_error("In items.json there are some wrong types");
        mp[(unsigned)iti->value.GetUint()]=String2Type[(std::string)itt->value.GetString()];
    }
    std::cerr<<"types loaded\n";
    return mp;
}

std::vector<unsigned> TypesHandler::getBuildingsIds()
{
    std::vector<unsigned> v;
    for (auto pr:tps) v.push_back(pr.first);
    return v;
}

Types TypesHandler::getTypeById(unsigned id)
{
    if (TypesHandler::tps.count(id)!=0)
        return TypesHandler::tps[id];
    return Types::Count;
}

Types TypesHandler::getTypeById(ID<>& id)
{
    return TypesHandler::getTypeById(id.id);
}

//---------------------------------------------------------------------------------

void RecipyHandler::addItem(unsigned id)
{
    recepies[id]={};
    auto prodLists = json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "production.json");
    auto arr=(*prodLists)["recipes"].GetArray();
    rapidjson::Value::ConstMemberIterator it;
    for (auto elem=arr.begin();elem!=arr.end();elem++)
    {
        it=elem->FindMember("id");
        assert (it!=elem->MemberEnd());
        unsigned recipe_id= it->value.GetUint();
        unsigned count = getValueById<unsigned>(arr,recipe_id,"count");

        auto reqList = new MaterialList(count);
        reqList->time = getValueById<float>(arr,recipe_id,"time");

        auto cons=getValueById<rapidjson::GenericArray<true,rapidjson::Value>>(arr,recipe_id,"consumes");
        auto req=getValueById<rapidjson::GenericArray<true,rapidjson::Value>>(arr,recipe_id,"requirements");

        for (unsigned i = 0; i < count; i++) {
            reqList->consumes[i] = cons[i].GetInt();
            reqList->ids[i] = req[i].GetUint();
        }
        recepies[id].emplace(std::make_pair(recipe_id,reqList));
    }
}


std::map<unsigned, std::map<unsigned,std::shared_ptr<MaterialList>>> RecipyHandler::recepies={};

MaterialList* RecipyHandler::getRequirementsById(ID<> BuildingId, unsigned recipy_id)
{
    char buf[1000];
    sprintf(buf,"Object with id %i do not have recipy with id %i",BuildingId.id,recipy_id);
    if (recepies.count(BuildingId.id)==0) addItem(BuildingId.id);
    if (recepies[BuildingId.id].count(recipy_id)==0) throw std::invalid_argument((const char *)buf);
    return new MaterialList(*recepies[BuildingId.id][recipy_id]); 
}

const std::map<unsigned,std::shared_ptr<MaterialList>>& RecipyHandler::getRequirementsList(ID<> BuildingId)
{
    if (recepies.count(BuildingId.id)==0) addItem(BuildingId.id);
    return recepies[BuildingId.id];
}

//-------------------------------------------------------------------------
sf::Texture& TextureHandler::getTextureById (unsigned id, Directions d) {
    if (TextureHandler::textures.count(id))
        if (TextureHandler::textures[id].count(d))return *TextureHandler::textures.at(id).at(d);
    auto ihandler = json_handling::getJsonDocument( // it's revolution, johny
        "./resources/config/items/" + json_communicate::getUrlById(id) + "main.json");
    std::string path="./resources/includes/"+json_communicate::getNameById(id)+"/"+
    json_communicate::getNameById(id)+"-"+suffix[d]
    +(std::string)((*ihandler)["image_format"].GetString());
    std::cout<<path<<'\n';
    std::shared_ptr<sf::Texture> texteure(new sf::Texture(path));
    TextureHandler::textures[id].emplace(d,texteure);
    return *texteure;
}