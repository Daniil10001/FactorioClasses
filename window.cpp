//
// Created by  Владимир Малахов on 31.03.2025.
//

#include "window.hpp"

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

//void Window::drawTiled(Object *obj, point<long long> position) {
//    obj->
//}
