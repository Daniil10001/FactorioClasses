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
#include "sessionlogic.hpp"

using GUI_TYPE_nps::GUI_TYPE;

std::vector<sf::Font> GUI_C::fonts ={};

GUI_ELEMENT::GUI_ELEMENT(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color)
{
    rect.setPosition(pos);
    rect.setSize(dims);
    rect.setFillColor(bg_color);
    rect.setOutlineThickness(1);
    rect.setOutlineColor({255,255,255});

    GUI_TYPE type = GUI_TYPE::DEFAULT;
}

GUI_ELEMENT::~GUI_ELEMENT() {
    for (auto child : children)
        delete child;
}

void GUI_ELEMENT::draw(sf::RenderWindow& window) {
    for (auto child : children) {
        child->draw(window);
    }

    window.draw(rect);
}

void GUI_ELEMENT::setPosition(sf::Vector2f pos)
{
    for (GUI_ELEMENT* child : children)
        child->setPosition(pos + rect.getPosition() - child->getPosition());

    rect.setPosition(pos);
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

void GUI_ELEMENT::pushChild(GUI_ELEMENT *child) {
    children.push_back(child);
}


TextWidget::TextWidget(sf::Font &font) : text(font) {
    type = GUI_TYPE::TextWidget;
}

TextWidget::TextWidget(sf::Vector2f pos, sf::Vector2f dims, sf::Color bg_color,
               sf::Font& font, sf::Color color, std::string textT) :
               GUI_ELEMENT(pos, dims, bg_color),text(font)
{
    text.setString(textT);
    text.setFillColor(color);
    text.setPosition(pos);
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
    text.setPosition(pos);
}

void TextWidget::setTextSize(unsigned int points) {
    text.setCharacterSize(points);
}

void TextWidget::draw(sf::RenderWindow &window) {
    for (auto child : children)
        child->draw(window);

    window.draw(rect);
    window.draw(text);
}



bool GUI_C::isHovering(sf::Vector2i mouse_pos, GUI_ELEMENT &elem) {
    return (((float)mouse_pos.x - elem.getPosition().x) <= elem.getSize().x &&
            ((float)mouse_pos.x - elem.getPosition().x) >= 0 &&

            ((float)mouse_pos.y - elem.getPosition().y) <= elem.getSize().y &&
            ((float)mouse_pos.y - elem.getPosition().y) >= 0);
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
    newButton->setTextSize(10);
    newButton->id = id;

    buttons.push_back(newButton);

    return newButton;
}

void GUI_C::attachWidget(GUI_ELEMENT *widg) {
    widgets.push_back(widg);
}

void GUI_C::attachInfo(GUI_ELEMENT *elem, Object &obj) {
    infos.insert_or_assign(&obj, elem);
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
//        std::cout << buttons[i]->getSize().x << " " << buttons[i]->getSize().y << std::endl;
    }

    for (unsigned i = 0; i < rows * columns; i++) {
        float x = pos.x + margin;
        for (unsigned col_width_scan = 0; col_width_scan < i % columns; col_width_scan++)
            x += max_col_width[col_width_scan] + margin;

        float y = pos.y + margin;
        for (unsigned row_height_scan = 0; row_height_scan < i / columns; row_height_scan++)
            y += max_row_height[row_height_scan] + margin;
//        std::cout<< "Button at " << x <<" "<< y <<std::endl;

        buttons[i]->setPosition({x, y});
    }

}

void GUI_C::loadFont(std::string filepath) {
    fonts.emplace_back(filepath);
}





Window::Window(sf::VideoMode dims, std::string title, int fps, bool isFullScreen) :
    window(dims, title, sf::Style::Resize),dims(dims), title(title), fps(fps), isFullScreen(isFullScreen), 
    pixels_per_tile(5), tile_texture("resources/includes/Tile/Tile.jpg"),

    deleteIcon("resources/includes/Delete/delete.png"), deleteSpriton(deleteIcon)
{
    window.setFramerateLimit(fps);
    currGhost = nullptr;

    deleteSpriton.setScale({20 / (float)deleteSpriton.getTextureRect().size.x,
                            20 / (float)deleteSpriton.getTextureRect().size.y});
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

const sf::Vector2f Window::Grid2Window(point<long long> p) {
    return sf::Vector2f(p.x * pixels_per_tile * upscale + window_start.x,
                        p.y * pixels_per_tile * upscale + window_start.y);
}

const point<long long> Window::Window2Grid(sf::Vector2f pos) {
    return point<ll>((pos.x - window_start.x) / pixels_per_tile / upscale,
                     (pos.y - window_start.y) / pixels_per_tile / upscale);
}




void Window::addGhost(Object *obj) {
    placeGhost();

    currGhost = obj;
    createSprite(obj);

    objs.at(obj).setColor(sf::Color(96, 96, 255));
}

void Window::drawGroundTiles() {
    sf::Sprite tile(tile_texture);

    auto left_top_corner = Window2Grid({0,0});

//    std::cout<<left_top_corner.x << left_top_corner.y <<std::endl;
    tile.setScale({pixels_per_tile * upscale / tile.getTextureRect().size.x,
                   pixels_per_tile * upscale / tile.getTextureRect().size.y});

    int64_t width = (int64_t)((float)window.getSize().x / (float)pixels_per_tile / upscale + 1.);
    int64_t height = (int64_t)((float)window.getSize().y / (float)pixels_per_tile / upscale + 1.);

//    std::cout<<width<<" "<<height<<std::endl;
    for (int64_t i = -1; i <= width; i++)
        for (int64_t j = -1; j <= height; j++) {
            tile.setPosition(Grid2Window({left_top_corner.x + i, left_top_corner.y + j}));
            window.draw(tile);
        }
}

sf::Sprite& Window::createSprite(Object* obj) {
    objs.emplace(obj, TextureHandler::getTextureById(obj->getId().id));
    return objs.at(obj);
}

void Window::invokeDeletion() {
    auto beingDeleted = hoversWhat(sf::Mouse::getPosition(window));

    if (!beingDeleted)
        return;

    deleteSprite(beingDeleted);
    deletionInvoked= false;
}

void Window::deleteSprite(Object *obj) {
    session.delFromLayerB(obj);
    objs.erase(obj);
}

//void Window::rotateSprite(Building *obj) {
//    switch (obj->getDirection().get()) {
//        case Directions::UP:
//            obj->getDirection().dir()
//    }
//}

bool Window::isHovering(sf::Vector2i mouse_pos, Object &elem) {
    auto selGrid = Window2Grid((sf::Vector2f)mouse_pos);
    return ((selGrid.x - elem.getPosition().x) <= elem.getSize().x - 1 &&
            (selGrid.x - elem.getPosition().x) >= 0 &&

            (selGrid.y - elem.getPosition().y) <= elem.getSize().y - 1 &&
            (selGrid.y - elem.getPosition().y) >= 0);
}

Object *Window::hoversWhat(sf::Vector2i mouse_pos) {
    for (const auto& obj : objs)
        if (isHovering(mouse_pos, *obj.first))
            return obj.first;

    return nullptr;
}

void Window::updatePosition(Object* obj) {
    auto& this_sprite = objs.at(obj);

    if (obj == currGhost) {
        auto currMouse = sf::Mouse::getPosition(window);

        // may cause an error
        currGhost->setPosition(Window2Grid((sf::Vector2f)currMouse));

        this_sprite.setPosition(Grid2Window(currGhost->getPosition()));
        this_sprite.setScale({
                                     ((float)obj->getSize().x * pixels_per_tile * upscale) / (float)this_sprite.getTextureRect().size.x,
                                     ((float)obj->getSize().y * pixels_per_tile * upscale) / (float)this_sprite.getTextureRect().size.y
                             });


        return;
    }

    this_sprite.setPosition(Grid2Window(obj->getPosition()));

    this_sprite.setScale({
                                 ((float)obj->getSize().x * pixels_per_tile * upscale) / (float)this_sprite.getTextureRect().size.x,
                                 ((float)obj->getSize().y * pixels_per_tile * upscale) / (float)this_sprite.getTextureRect().size.y
                         });

}

void Window::updatePositionAll() {
    for (auto x: objs)
        updatePosition(x.first);
}

void Window::invokeBuildingInfo(Object &obj) {
    if (auto iter = GUI.infos.find(&obj); iter != GUI.infos.end()) {
        delete iter->second;
        GUI.infos.erase(iter);
        return;
    }

    sf::Vector2f pos = {objs.at(&obj).getPosition().x, objs.at(&obj).getPosition().y - 100};
    sf::Vector2f dims = {200, 100};

    auto infoWindow = new GUI_ELEMENT(pos, dims, sf::Color(0,0,0,100));
    auto inventory = session.getBuildingInventory(&obj);

    float i = 0;
    for (auto& material : inventory) {
        std::string str = json_communicate::getNameById(material.getId().id) + std::string(": ") + std::to_string(material.get_quantity());
        infoWindow->pushChild((new TextWidget(
                {pos.x, pos.y + i}, dims, {0, 0, 0, 100},
                *GUI_C::fonts.begin(), {255, 255, 255},str)
                ));

        i += 20;
    }
//    infoWindow->pushChild();
    InfoOpened = true;

    GUI.attachInfo(infoWindow, obj);
}

void Window::draw(Object *obj) {
    updatePosition(obj);
    window.draw(objs.at(obj));
}

void Window::drawAll() {
    for (const auto& x: objs)
        Window::draw(x.first);
}

void Window::placeGhost() {
    if (!currGhost)
        return;
    if (deletionInvoked) return;

    try {
        createSprite(session.addToLayerB(currGhost->getId().id, currGhost->getPosition(), Directions::UP));
        objs.erase(currGhost);
        delete currGhost;

        currGhost = nullptr;
        ghostDirec = Directions::UP;
    }
    catch(const std::exception& e)
    {
        std::cerr<<e.what()<<'\n';
        return;
    }
}

bool Window::isGhost() {
    return currGhost;
}

void Window::drawGUI() {
    for (GUI_ELEMENT* elem: GUI.buttons) {
        (elem)->draw(window);

    }

    for (auto elem : GUI.widgets) {
        elem->draw(window);
    }

    for (auto elem : GUI.infos) {
        elem.second->draw(window);
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

            keysPressed.insert_or_assign(keyPressed->scancode, true);
        }

        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            keysPressed.insert_or_assign(keyReleased->scancode, false);
        }

        else if
            (const auto* mouseButtonPressed =
                    event->getIf<sf::Event::MouseButtonPressed>())
        {
            auto selectedBuilding = hoversWhat(sf::Mouse::getPosition(window));

            if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                if (deletionInvoked)
                    invokeDeletion();

                else if (!GUI.MouseClick(sf::Mouse::getPosition(window), this) &&
                    isGhost())
                    placeGhost();

                else if (selectedBuilding && selectedBuilding!=currGhost)
                    invokeBuildingInfo(*selectedBuilding);
            }
        }

        //
    }

    // keyboard keys handling
    for (auto iter = keysPressed.begin(); iter != keysPressed.end(); ++iter) {
        if ((iter->first == sf::Keyboard::Scancode::Up || iter->first == sf::Keyboard::Scancode::W) && iter->second)
            window_start += {0, upscale};

        if ((iter->first == sf::Keyboard::Scancode::Down || iter->first == sf::Keyboard::Scancode::S) && iter->second)
            window_start += {0, -upscale};

        if ((iter->first == sf::Keyboard::Scancode::Left || iter->first == sf::Keyboard::Scancode::A) && iter->second)
            window_start += {upscale, 0};

        if ((iter->first == sf::Keyboard::Scancode::Right || iter->first == sf::Keyboard::Scancode::D) && iter->second)
            window_start += {-upscale, 0};


        if (iter->first == sf::Keyboard::Scancode::LBracket && iter->second)
            upscale -= 0.3;

        if (iter->first == sf::Keyboard::Scancode::RBracket && iter->second)
            upscale += 0.3;
    }

    window.clear(sf::Color::Black);


    if (deletionInvoked) {
        deleteSpriton.setPosition((sf::Vector2f)sf::Mouse::getPosition(window) + sf::Vector2f{20,20});
        window.draw(deleteSpriton);
    }
    drawGroundTiles();
    drawAll();
    drawGUI();


    window.display();
}




//void Window::drawTiled(Object *obj, point<long long> position) {
//    obj->
//}
