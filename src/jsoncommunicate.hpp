//
// Created by  Владимир Малахов on 14.02.2025.
//

#ifndef jsoncommunicate_hpp__
#define jsoncommunicate_hpp__
#define ll long long
#include "interactioninterfaces.hpp"
#include <rapidjson/document.h>
#include"objectparametrshandler.hpp"
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
        //std::cout<<path<<'\n';
        //std::cout<<"deleted\n";
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

    template<typename T,class For,std::size_t N,const char (&C)[N]>
    static inline typename std::enable_if<std::is_same<T, unsigned>::value, T>::type
    get_property(unsigned id){
        static_assert(Checking::Propeties.check<For>(C));
        return (*json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"))[C].GetUint();
    }

    template<typename T,class For,std::size_t N,const char (&C)[N]>
    static inline typename std::enable_if<std::is_same<T, int>::value, T>::type
    get_property(unsigned id){
        static_assert(Checking::Propeties.check<For>(C));
        return (*json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"))[C].GetInt();
    }

    template<typename T,class For,std::size_t N,const char (&C)[N]>
    static inline typename std::enable_if<std::is_same<T, float>::value, T>::type
    get_property(unsigned id){
        static_assert(Checking::Propeties.check<For>(C));
        return (*json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"))[C].GetFloat();
    }

    template<typename T,class For,std::size_t N,const char (&C)[N]>
    static inline typename std::enable_if<std::is_same<T, std::string>::value, T>::type
    get_property(unsigned id){
        static_assert(Checking::Propeties.check<For>(C));
        return (*json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"))[C].GetString();
    }

    /*template<typename T,class For,std::size_t N,const char (&C)[N]>
    static inline typename std::enable_if<std::is_same<T, double>::value, T>::type
    get_property(unsigned id){
        static_assert(Checking::Propeties.check<For>(C));
        return (*json_handling::getJsonDocument("./resources/config/items/" + json_communicate::getUrlById(id) + "main.json"))[C].GetDouble();
    }*/// needed to be tested
};

class TypesHandler
{
    private:
    static std::map<unsigned,Types> generate();
    static std::map<unsigned,Types> tps;
    public:
    static std::vector<unsigned> getBuildingsIds();
    static Types getTypeById(unsigned id);
    static Types getTypeById(ID<>& id);
};

class TextureHandler
{
    static inline std::map<Directions,std::string> suffix={{Directions::UP,"up"},{Directions::LEFT,"left"},{Directions::RIGHT,"right"},{Directions::DOWN,"down"}};
    static std::map<unsigned, std::shared_ptr<sf::Texture>> textures;
    public:
    static sf::Texture& getTextureById (unsigned id, Directions d);
    static inline sf::Texture& getTextureById (unsigned id, Direction d=Direction(Directions::UP)){return getTextureById(id, d.dir());};
};

class RecipyHandler{
    static std::map<unsigned, std::map<unsigned,std::shared_ptr<MaterialList>>> recepies;
    static void addItem(unsigned id);
    public:
    static const std::map<unsigned,std::shared_ptr<MaterialList>>& getRequirementsList(ID<> BuildingId);
    static MaterialList* getRequirementsById(ID<> BuildingId, unsigned recipy_id=0);
};

#endif //FACTORIO_JSON_COMMUNICATE_H
