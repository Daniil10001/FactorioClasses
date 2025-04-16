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

namespace GUI_TYPE_nps {
    enum GUI_TYPE {
        Widget,
        Button,
        Lol
    };
}

using GUI_TYPE_nps::GUI_TYPE;

struct GUI_ELEMENT {
    sf::RectangleShape rect;

    bool visible;
    GUI_TYPE type;
    sf::Vector2f dims; // here in sfml's pixels
    sf::Vector2f pos; // top left corner
    sf::Color bg_color;

    // may be unused
    std::unique_ptr<GUI_ELEMENT*> children = nullptr; // for now there is only one child possible
};





struct Widget : GUI_ELEMENT {
    Widget(sf::Font& font) : text(font) {};

    sf::Text text;
    sf::Color color;
};

struct Button : Widget {
    Button(sf::Font& font) : Widget(font) {};

    sf::Color color; // color of the text

    std::function<void()> call; // for now, it's void
};

// not static because
class GUI_C {
public:
    std::vector<GUI_ELEMENT*> buttons;
    std::vector<GUI_ELEMENT*> widgets;

    static std::vector<sf::Font> fonts;

    GUI_C() {};

    ~GUI_C() {};

    bool isHovering(sf::Vector2i mouse_pos, GUI_ELEMENT &elem);

    bool MouseClick(sf::Vector2i mouse_pos);

    void createButton(sf::Vector2f pos, sf::Vector2f dims,
                             sf::Color bg_color, sf::Color text_color,
                             std::string text, std::function<void()> func);

    static void loadFont(std::string filepath);
};


class Window {
private:
    sf::RenderWindow window;



    sf::VideoMode dims;

    std::string title;

    int fps;
    bool isFullScreen;

    sf::Vector2f window_start;
    const uint64_t pixels_per_tile=100;
    float upscale=1;

    Object* currGhost; // for the time being it's left single


    // visualization stuff
    std::map<Object*, sf::Sprite> objs;




public:

    GUI_C GUI;

    Window(sf::VideoMode dims, std::string title, int fps, bool isFullScreen);

    Window(sf::VideoMode dims, int fps, bool isFullScreen);

    Window();

    ~Window();

    // render handling

    bool isOpen();

    const sf::Vector2f Window2Grid(point<ll> p);

    const point<ll> Grid2Window(sf::Vector2f grid);



    // SPRITES HANDLING
    void drawTiled(Object* obj, point<ll> position);

    void createSprite(Object* obj);

    void deleteSprite(Object* obj);

    // Position is calculated in session logic and written in Object
    // Here it is simply being transferred to sf::Sprite
    // obj key presence will not be checked
    void updatePosition(Object *obj);

    void updatePositionAll();



    // includes updatePosition
    void draw(Object *obj);

    void drawAll();

    // Adds a single ghost leaving a pointer mark in currGhost
    // Places previous ghost
    void addGhost(Object* obj);

    void placeGhost();

    bool isGhost(); // if ghost is present

    void drawGUI();

    void frame();

};


#endif
