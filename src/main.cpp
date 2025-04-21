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
    cout<<"program running"<<endl;
    Window session_window;
    GUI_C::loadFont("resources/fonts/SpaceGrotesk-Medium.ttf");
    cout<<session_window.GUI.fonts.begin()->getInfo().family;
//    session_window.GUI.createButton({0,0},{100,100}, {0,0,0}, {0,0,0}, "lolkek",
//                                    [](Window* window_ptr) {std::cout<<window_ptr->getTitle()<<std::endl;});

    CreateGhostButton* objectButtons[4];
    std::string buttonsnames[] = {"lol", "kek", "cheeeeeeburek", "shaverma"};
    int desired_ids[] = {1001,1001,1001,1001};
    for (unsigned i = 0; i < 4; i++) {
        objectButtons[i] = session_window.GUI.createCreateGhostButton({0,0}, {150, 100}, {255,255,0}, {255,0,0},
                                                           buttonsnames[i], desired_ids[i]);
    }
    session_window.GUI.createButtonGrid(2,2, {session_window.getWidth() * (float)0.75, 0}, 2, (Button**)objectButtons);

    //cout<<1<<endl;
    while (session_window.isOpen()) {
        session_window.frame();
        //cout<<2<<endl;
    }
    session_window.addGhost(new Object(24));



//    sf::Font font("resources/fonts/SpaceGrotesk-Medium.ttf");
//    cout<<font.getInfo().family;
    return 0;
}