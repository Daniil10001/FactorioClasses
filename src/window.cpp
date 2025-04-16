//
// Created by  Владимир Малахов on 31.03.2025.
//

#include "window.hpp"
#include "object.hpp"
#include "jsoncommunicate.hpp"
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

std::vector<sf::Font> GUI_C::fonts ={};

bool GUI_C::isHovering(sf::Vector2i mouse_pos, GUI_ELEMENT &elem) {
    if (((float)mouse_pos.x - elem.pos.x) <= elem.dims.x && ((float)mouse_pos.x - elem.pos.x) >= 0 &&
        ((float)mouse_pos.y - elem.pos.y) <= elem.dims.y && ((float)mouse_pos.y - elem.pos.y) >= 0)
        return true;

    return false;
}

bool GUI_C::MouseClick(sf::Vector2i mouse_pos) {
    for (GUI_ELEMENT *elem: buttons)
        if (isHovering(mouse_pos, *elem)) {
            ((Button *) elem)->call();
            return true;
        }
    return false;
}

void GUI_C::createButton(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color, sf::Color text_color,
                               std::string text, std::function<void()> func) {
    Button* newButton = new Button(*(fonts.begin()));
    newButton->type = GUI_TYPE::Button;
    newButton->visible = true;
    newButton->pos = pos;
    newButton->dims = dims;
    newButton->bg_color = bg_color;
    newButton->color = text_color;

    newButton->text.setString(text);
    newButton->text.setFillColor(text_color);
    newButton->text.setCharacterSize(24);

    newButton->rect.setPosition(pos);
    newButton->rect.setSize(dims);

    newButton->call = func;

    buttons.push_back(newButton);
}

void GUI_C::loadFont(std::string filepath) {
    fonts.emplace_back(filepath);
}





Window::Window(sf::VideoMode dims, std::string title, int fps, bool isFullScreen) :
    dims(dims), title(title), fps(fps), isFullScreen(isFullScreen), pixels_per_tile(5),
    window(dims, title, sf::Style::Resize)
{
    window.setFramerateLimit(fps);
    currGhost = nullptr;
}

Window::Window(sf::VideoMode dims, int fps, bool isFullScreen) :
        Window(dims, "Title holder", fps, isFullScreen) {};

Window::Window() : Window(sf::VideoMode({1920,1080}), 60, false) {};

Window::~Window() {};

bool Window::isOpen() {
    return window.isOpen();
}

const sf::Vector2f Window::Window2Grid(point<long long> p) {
    return sf::Vector2f(p.x / pixels_per_tile / upscale,
                        p.y / pixels_per_tile / upscale);
}

const point<long long> Window::Grid2Window(sf::Vector2f grid) {
    return point<ll>(grid.x * pixels_per_tile * upscale,
                     grid.y * pixels_per_tile * upscale);
}




void Window::addGhost(Object *obj) {
    placeGhost();

    currGhost = obj;
    createSprite(obj);

    objs.at(obj).setColor(sf::Color(0, 0, 255));
}

void Window::createSprite(Object* obj) {
    objs.emplace(obj, json_communicate::getTextureById(obj->getId().id));
}

void Window::deleteSprite(Object *obj) {
    objs.erase(obj);
}

void Window::updatePosition(Object* obj) {
    auto temp = obj->getPosition();

    if (obj == currGhost) {
        auto currMouse = sf::Mouse::getPosition(window);

        // may cause an error
        objs.at(obj).setPosition({
            (float)((uint64_t)currMouse.x / pixels_per_tile) * upscale,
            (float)((uint64_t)currMouse.y / pixels_per_tile) * upscale
        });

        return;
    }

    objs.at(obj).setPosition(Window2Grid(temp) * (float)pixels_per_tile * (float)upscale + window_start);

}

void Window::updatePositionAll() {
    for (auto x: objs)
        updatePosition(x.first);
}

void Window::draw(Object *obj) {
    updatePosition(obj);
    window.draw(objs.at(obj));
}

void Window::drawAll() {
    for (auto x: objs)
        Window::draw(x.first);
}

void Window::placeGhost() {
    if (!currGhost)
        return;

    objs.at(currGhost).setColor(sf::Color(255,255,255));

    /*
     * Some behaviour here regarding placing a building
     */

    currGhost = nullptr;
}

bool Window::isGhost() {
    return currGhost;
}

void Window::drawGUI() {
    for (GUI_ELEMENT* elem: GUI.buttons) {
        if (elem->type == GUI_TYPE::Button) {
//            std::cout<<"lolkek";
            window.draw(((Button*)elem)->rect);
            window.draw(((Button*)elem)->text);
        }
    }
}




void Window::frame() {


    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }

        else if
            (const auto* mouseButtonPressed =
                    event->getIf<sf::Event::MouseButtonPressed>())
        {
            // invoken only if not
            if (mouseButtonPressed->button == sf::Mouse::Button::Left &&
                !GUI.MouseClick(sf::Mouse::getPosition(window)) &&
                isGhost())
            {
                placeGhost();
            }


        }

        //
    }

    window.clear(sf::Color::Black);

//    drawAll();
    drawGUI();

    window.display();
}




//void Window::drawTiled(Object *obj, point<long long> position) {
//    obj->
//}
