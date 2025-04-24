//
// Created by  Владимир Малахов on 31.03.2025.
//

#ifndef FACTORIO_WINDOW_HPP__
#define FACTORIO_WINDOW_HPP__

#include <iostream>
#include <map>
#include <array>
#include <functional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "interactioninterfaces.hpp"
#include "object.hpp"
#include "sessionlogic.hpp"

namespace GUI_TYPE_nps {
    enum GUI_TYPE {
        DEFAULT,
        TextWidget,
        Button,
        CreateButton
    };
}

using GUI_TYPE_nps::GUI_TYPE;

class GUI_ELEMENT {
protected:
    sf::RectangleShape rect;



    // may be unused
    std::vector<GUI_ELEMENT*> children; // for now there is only one child possible

public:
    GUI_TYPE type;

    GUI_ELEMENT() {type = GUI_TYPE::DEFAULT;}

    GUI_ELEMENT(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color);

    virtual ~GUI_ELEMENT();

    virtual void draw(sf::RenderWindow&);

    virtual void setPosition(sf::Vector2f);

    virtual void setBGColor(sf::Color);

    virtual void setVisible();

    virtual void setInvisible();

    virtual void setSize(sf::Vector2f size);

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    sf::Color getBGColor();

    void pushChild(GUI_ELEMENT*);

};

class TextWidget : public GUI_ELEMENT {
protected:
    sf::Text text;
    sf::Color color;

public:


    explicit TextWidget(sf::Font& font);

    TextWidget(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color,
               sf::Font& font, sf::Color color, std::string text);
    
    TextWidget(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color,
                sf::Font& font, sf::Color color, std::string textT, float scale);

    void draw(sf::RenderWindow&) override;

    void setString(std::string&);

    void setPosition(sf::Vector2f) override; // relative to basic element (rectangle)

    void setColor(sf::Color); // color of the text

    void setTextSize(unsigned points);

};

class Window;

struct Button : public TextWidget {
    explicit Button(sf::Font& font) : TextWidget(font) {
        type = GUI_TYPE::Button;
    };



    sf::Color color; // color of the text

    std::function<void(Window*)> call; // return is void, but may be extended


};

struct CreateGhostButton;


// not static because
class GUI_C {
public:
    std::vector<GUI_ELEMENT*> buttons;
    std::vector<GUI_ELEMENT*> widgets;
    std::map<Object*, GUI_ELEMENT*> infos;

    static std::vector<sf::Font> fonts;

    GUI_C() {};

    ~GUI_C() {};

    bool isHovering(sf::Vector2i mouse_pos, GUI_ELEMENT &elem);

    bool MouseClick(sf::Vector2i mouse_pos, Window *window_ptr);

    Button* createButton(sf::Vector2f pos, sf::Vector2f dims,
                             sf::Color bg_color, sf::Color text_color,
                             std::string text, std::function<void(Window*)> func);

    CreateGhostButton* createCreateGhostButton(sf::Vector2f pos, sf::Vector2f dims,
                                               sf::Color bg_color, sf::Color text_color,
                                               std::string text, unsigned id);

    void attachWidget(GUI_ELEMENT*);

    void attachInfo(GUI_ELEMENT*, Object*);

    // it is supposed that Button is fully initialized
    void createButton(Button *new_button);

    // Buttons given in a form of an array, initialized positions will be overwritten
    static void createButtonGrid(unsigned rows, unsigned columns, sf::Vector2f pos, float margin, Button **buttons);

    static void loadFont(std::string filepath);
};


class Window {
private:
    sf::RenderWindow window;

    SessionHandler session;

    sf::VideoMode dims;

    std::string title;

    int fps;
    bool isFullScreen;

    // sfml = tile * pixels_per_tile + window_start
    sf::Vector2f window_start = {0,0};
    const int64_t pixels_per_tile=100;
    float upscale=10;

    std::map<sf::Keyboard::Scancode, bool> keysPressed;

    Object* currGhost; // for the time being it's left single
    Directions ghostDirec = Directions::UP;

    bool InfoOpened = false;

    sf::Texture deleteIcon;
    sf::Sprite deleteSpriton;

    // visualization stuff
    std::map<Object*, sf::Sprite> objs;
    sf::Texture tile_texture;

    GUI_ELEMENT* creteBuildingInfo(Object *obj);
    void updateBuildingInfo();
public:
    bool deletionInvoked = false;

    GUI_C GUI;

    Window(sf::VideoMode dims, std::string title, int fps, bool isFullScreen);

    Window(sf::VideoMode dims, int fps, bool isFullScreen);

    Window();

    ~Window();

    std::string getTitle();

    int getWidth();
    int getHeight();

    // render handling

    bool isOpen();

    const sf::Vector2f Grid2Window(point<ll> p);

    const point<ll> Window2Grid(sf::Vector2f pos);



    // SPRITES HANDLING

    void drawGroundTiles();

    sf::Sprite& createSprite(Object* obj);

    void invokeDeletion();

    void deleteSprite(Object *);

    void rotateSprite(Building *);

    bool isHovering(sf::Vector2i mouse_pos, Object &elem); // is hovering sprite

    Object* hoversWhat(sf::Vector2i mouse_pos);

    void updatePosition(Object *);      // Position is calculated in session logic and written in Object
                                        // Here it is simply being transferred to sf::Sprite
                                        // obj key presence will not be checked

    void updatePositionAll();


    void invokeBuildingInfo(Object*);

    void drawWidget(GUI_ELEMENT*);

    void draw(Object *obj); // includes updatePosition

    void drawAll();


    void addGhost(Object* obj); // Adds a single ghost leaving a pointer mark in currGhost
                                // Places previous ghost

    void placeGhost();

    bool isGhost(); // if ghost is present

    void drawGUI();

    void frame();

};

struct CreateGhostButton : Button {
    ID<> id;
    CreateGhostButton(sf::Font& font, ID<> id) : Button(font), id(id)
    {
        call = [this](Window* window_ptr) {
            std::cout << "Button with " << this->id.id<<std::endl;
            Object* obj(new Object(this->id));
            window_ptr->addGhost(obj);
            std::cout<<"object being created"<<std::endl;
        };
        type = GUI_TYPE::CreateButton;
    };


};


#endif
