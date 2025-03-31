//
// Created by  Владимир Малахов on 31.03.2025.
//

#ifndef FACTORIO_WINDOW_HPP__
#define FACTORIO_WINDOW_HPP__

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window {
private:
    sf::RenderWindow window;
    sf::VideoMode dims;

    std::string title;

    int fps;
    bool isFullScreen;

    // visualization stuff
    std::stack<sf::Sprite> sprites;
public:
    Window(sf::VideoMode dims, std::string title, int fps, bool isFullScreen) :
        dims(dims), title(title), fps(fps), isFullScreen(isFullScreen),
        window(dims, title, sf::Style::Resize)
    {
        window.setFramerateLimit(fps);
    }

    Window(sf::VideoMode dims, int fps, bool isFullScreen) :
        Window(dims, "Title holder", fps, isFullScreen) {};

    ~Window();

    // sprites handling


};


#endif
