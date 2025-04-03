//
// Created by  Владимир Малахов on 31.03.2025.
//

#include "window.hpp"
#include "object.hpp"
#include "jsoncommunicate.hpp"

Window::Window(sf::VideoMode dims, std::string title, int fps, bool isFullScreen) :
    dims(dims), title(title), fps(fps), isFullScreen(isFullScreen), pixels_per_tile(5),
    window(dims, title, sf::Style::Resize)
{
    window.setFramerateLimit(fps);

}

Window::Window(sf::VideoMode dims, int fps, bool isFullScreen) :
        Window::Window(dims, "Title holder", fps, isFullScreen) {};

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


void Window::createSprite(Object* obj) {
    objs.emplace(obj, json_communicate::getTextureById(obj->getId()));

    if (obj->isGhost) {
        objs.at(obj).setColor(sf::Color(0, 0, 255));
        currGhost = obj;
    }
}

void Window::deleteSprite(Object *obj) {
    objs.erase(obj);
}

void Window::updatePosition(Object* obj) {
    auto temp = obj->getPosition();

    if (obj->isGhost) {
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
    
}

void Window::frame() {
    window.clear(sf::Color::Black);
    drawAll();

    window.display();
}

//void Window::drawTiled(Object *obj, point<long long> position) {
//    obj->
//}
