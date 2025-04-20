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

using GUI_TYPE_nps::GUI_TYPE;

std::vector<sf::Font> GUI_C::fonts ={};

GUI_ELEMENT::GUI_ELEMENT(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color)
{
    rect.setPosition(pos);
    rect.setSize(dims);
    rect.setFillColor(bg_color);

    GUI_TYPE type = GUI_TYPE::DEFAULT;
}

void GUI_ELEMENT::draw(sf::RenderWindow& window) {
    window.draw(rect);
}

void GUI_ELEMENT::setPosition(sf::Vector2f pos)
{
    rect.setPosition(pos);
    for (GUI_ELEMENT* child : children)
        child->rect.setOrigin(pos);
}

void GUI_ELEMENT::setVisible() {
    sf::Color newCol = rect.getFillColor();
    newCol *= {1,1,1, 0};
    rect.setFillColor(newCol);
}

void GUI_ELEMENT::setInvisible() {
    sf::Color newCol = rect.getFillColor();
    newCol += {0,0,0, 255};
    rect.setFillColor(newCol);
}

void GUI_ELEMENT::setBGColor(sf::Color col) {
    rect.setFillColor(col);
}

void GUI_ELEMENT::setSize(sf::Vector2f size) {
    rect.setSize(size);
}

sf::Vector2f GUI_ELEMENT::getPosition() {
    return rect.getPosition();
}

sf::Vector2f GUI_ELEMENT::getSize() {
    return rect.getSize();
}

sf::Color GUI_ELEMENT::getBGColor() {
    return rect.getFillColor();
}


TextWidget::TextWidget(sf::Font &font) : text(font) {
    type = GUI_TYPE::TextWidget;
}

TextWidget::TextWidget(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color,
               sf::Font& font, sf::Color color, std::string textT) :
               text(font), GUI_ELEMENT(pos, dims, bg_color)
{
    text.setString(textT);
    text.setFillColor(color);
    text.setOrigin(pos);
    text.setCharacterSize(10);

    type = GUI_TYPE::TextWidget;
}

void TextWidget::setString(std::string& str) {
    text.setString(str);
}

void TextWidget::setColor(sf::Color col) {
    text.setFillColor(col);
}

void TextWidget::setPosition(sf::Vector2f pos) {
    rect.setPosition(pos);
    text.setOrigin(pos);
}

void TextWidget::setTextSize(unsigned int points) {
    text.setCharacterSize(points);
}

void TextWidget::draw(sf::RenderWindow &window) {
    window.draw(rect);
    window.draw(text);
}



bool GUI_C::isHovering(sf::Vector2i mouse_pos, GUI_ELEMENT &elem) {
    if (((float)mouse_pos.x - elem.getPosition().x) <= elem.getSize().x &&
        ((float)mouse_pos.x - elem.getPosition().x) >= 0 &&

        ((float)mouse_pos.y - elem.getPosition().y) <= elem.getPosition().y &&
        ((float)mouse_pos.y - elem.getPosition().y) >= 0)
            return true;

    return false;
}

bool GUI_C::MouseClick(sf::Vector2i mouse_pos, Window *window_ptr) {
    for (GUI_ELEMENT *elem: buttons)
        if (isHovering(mouse_pos, *elem)) {
            ((Button *) elem)->call(window_ptr);
            return true;
        }
    return false;
}

Button* GUI_C::createButton(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color, sf::Color text_color,
                               std::string text, std::function<void(Window*)> func) {
    auto newButton = new Button(*(fonts.begin()));
    newButton->setPosition(pos);
    newButton->setSize(dims);
    newButton->setBGColor(bg_color);
    newButton->setColor(text_color);

    newButton->setString(text);
    newButton->setTextSize(24);

    newButton->call = func;

    buttons.push_back(newButton);

    return newButton;
}

CreateGhostButton *
GUI_C::createCreateGhostButton(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color, sf::Color text_color,
                               std::string text, unsigned int id) {
    auto newButton = new CreateGhostButton(*(fonts.begin()), id);
    newButton->setPosition(pos);
    newButton->setSize(dims);
    newButton->setBGColor(bg_color);
    newButton->setColor(text_color);

    newButton->setString(text);
    newButton->setTextSize(24);

    buttons.push_back(newButton);

    newButton->id = id;

    buttons.push_back(newButton);

    return newButton;
}

void GUI_C::createButton(Button *new_button) {
    buttons.push_back(new_button);
}

void GUI_C::createButtonGrid(unsigned rows, unsigned columns, sf::Vector2f pos, float margin, Button **buttons) {
    std::vector<float> max_row_height(rows, 0);
    std::vector<float> max_col_width(columns, 0);

    for (unsigned i = 0; i < rows * columns; i++) {
        max_row_height[i / columns] = std::max(max_row_height[i / columns], buttons[i]->getSize().y);
        max_col_width[i % rows] = std::max(max_col_width[i % columns], buttons[i]->getSize().x);
        std::cout << buttons[i]->getSize().x << " " << buttons[i]->getSize().y << std::endl;
    }

    for (unsigned i = 0; i < rows * columns; i++) {
        float x = pos.x + margin;
        for (unsigned col_width_scan = 0; col_width_scan < i % columns; col_width_scan++)
            x += max_col_width[col_width_scan] + margin;

        float y = pos.y + margin;
        for (unsigned row_height_scan = 0; row_height_scan < i / columns; row_height_scan++)
            y += max_row_height[row_height_scan] + margin;
        std::cout<< "Button at " << x <<" "<< y <<std::endl;

        buttons[i]->setPosition({x, y});
    }

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

Window::Window() : Window(sf::VideoMode({1280,720}), 60, false) {};

Window::~Window() {};

std::string Window::getTitle() {return title;}

int Window::getWidth() {return window.getSize().x;}

int Window::getHeight() {return window.getSize().y;}

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
        if (elem->type == GUI_TYPE::CreateButton)
            ((CreateGhostButton*)elem)->draw(window);

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
                !GUI.MouseClick(sf::Mouse::getPosition(window), this) &&
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
