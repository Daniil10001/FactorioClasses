#include "iostream"
#include "material.hpp"
#include "interactioninterfaces.hpp"
#include "factory.hpp"
#include "inserter.hpp"
#include "jsoncommunicate.hpp"
#include "window.hpp"
using std::cout, std::endl;

int main()
{
    Window session_window;
    GUI_C::loadFont("resources/fonts/SpaceGrotesk-Medium.ttf");
    cout<<session_window.GUI.fonts.begin()->getInfo().family;
    session_window.GUI.createButton({0,0},{100,100}, {0,0,0}, {0,0,0}, "lolkek",
                                    [](Window* window_ptr) {std::cout<<window_ptr->getTitle()<<std::endl;});

    //cout<<1<<endl;
    while (session_window.isOpen()) {
        session_window.frame();
        //cout<<2<<endl;
    }



//    sf::Font font("resources/fonts/SpaceGrotesk-Medium.ttf");
//    cout<<font.getInfo().family;
    return 0;
}