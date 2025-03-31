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

    // returns first recipe by default
    static MaterialList* getRequirementsById(unsigned id) {
        return getRequirementsById(id, 0);
    }

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

    static MaterialList* getRequirementsById(unsigned id, unsigned recipe_id);

    static sf::Texture& getTextureById (unsigned id);
};


class texture_handler
{
    public:
    static std::map<unsigned, std::shared_ptr<sf::Texture>> textures;
};


#endif //FACTORIO_JSON_COMMUNICATE_H
