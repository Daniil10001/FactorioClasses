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

    Button* objectButtons[6];
    std::string buttonsnames[] = {"Miner", "Inserter", "Chest", "Conveyor", "Fabricator"};
    int desired_ids[] = {1001,1002,1003,1004, 1005};
    for (unsigned i = 0; i < 5; i++) {
        objectButtons[i] = session_window.GUI.createCreateGhostButton({0,0}, {150, 100}, {255,255,0}, {255,0,255},
                                                                      buttonsnames[i], desired_ids[i]);
    }
    objectButtons[5] = session_window.GUI.createButton({0,0}, {150,150}, {255, 0, 0}, {255,255,255}, "DELETE",
                                                       [](Window* wind){wind->deletionInvoked = !(wind->deletionInvoked);});

    session_window.GUI.createButtonGrid(3,2, {session_window.getWidth() * (float)0.75, 0}, 2, (Button**)objectButtons);

    //cout<<1<<endl;
    while (session_window.isOpen()) {
        session_window.frame();
        //cout<<2<<endl;
    }


//    sf::Font font("resources/fonts/SpaceGrotesk-Medium.ttf");
//    cout<<font.getInfo().family;
    return 0;
}