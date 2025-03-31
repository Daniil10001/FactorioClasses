//
// Created by  Владимир Малахов on 31.03.2025.
//

#ifndef FACTORIO_WINDOW_HPP__
#define FACTORIO_WINDOW_HPP__

#include <iostream>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "interactioninterfaces.hpp"

class Window {
private:
    sf::RenderWindow window;
    sf::VideoMode dims;

    std::string title;

    int fps;
    bool isFullScreen;

    point<ll> window_start;
    const uint64_t pixels_per_tile=100;
    float upscale=1;

    // visualization stuff
    std::map<Object*, sf::Sprite> objs;
public:
    Window(sf::VideoMode dims, std::string title, int fps, bool isFullScreen);

    Window(sf::VideoMode dims, int fps, bool isFullScreen);

    ~Window();

    // render handling
    bool isOpen();

    const sf::Vector2f Window2Grid(point<ll> p);

    const point<ll> Grid2Window(sf::Vector2f grid);

    void drawTiled(Object* obj, point<ll> position);

    void createSprite(Object* obj);

    void deleteSprite(Object* obj);
};


#endif
