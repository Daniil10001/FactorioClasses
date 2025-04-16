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
<<<<<<< HEAD
    //cout<<Object::type<<" "<<Factory::type<<endl;
    cout<<"test Materials\n";
    Material m1=Material(40,1);
    Material m2=Material(10,2);
    Material m3=Material(50,1);
=======
//    cout<<"test Materials\n";
//    Material m1=Material(40,1);
//    Material m2=Material(10,2);
//    Material m3=Material(50,1);
//
//    cout<<m1.get_quantity()<<'\n';
//    cout<<"adding BAD and OK\n";
//    cout<<ActionResult::BAD<<" "<<ActionResult::OK<<'\n';
//    cout<<m1+m2<<" "<<m1+m3<<'\n';
//    cout<<m1.get_quantity()<<' '<<m2.get_quantity()<<' '<<m3.get_quantity()<<'\n';
//
//
//    cout<< "checking if json works" << endl;
//    //
//        cout << json_communicate::getNameById(0)<<endl;
//        cout << json_communicate::getNameById(1001)<<endl;
//        cout<<"test fabric produce\n";
//
//    point<ll> p(0,0);
//    Direction d=Direction(Directions::UP);
//    Factory f(1001,p,d);
//    #if DLEVEL==0
//        f.printInventory();
//    #endif
//    f.produce();
//    f.produce();
//    f.produce();
//    #if DLEVEL==0
//        f.printInventory();
//    #endif
//    cout<<f.get_material_quantity(1)<<'\n';
//
//    Factory f2(1001,p,d);
//    Factory f3(1001,p,d);
//    Factory f4(1001,p,d);
//
//    cout<<"test connections\n";
//    MakeConnFull(&f,&f2, Connections::Standart);
//    MakeConnFull(&f4,&f3, Connections::Standart);
//    MakeConnFull(&f3,&f2, Connections::Standart);
//    MakeConnStrait(&f,&f2, Connections::Chain);
//
//    cout<<"Check connection:\n need to be 0 1 :";
//    cout<<f.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
//    cout<<"Check connection:\n need to be 1 1 :";
//    cout<<f3.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f3.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
//    cout<<"Check connection:\n need to be 2 0 :";
//    cout<<f2.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f2.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
//
//    //dummy and insertion tests
//    cout<<"Checking inserters and dummy\n";
//    Dummy d1(p), d2(p);
//    Inserter ins(1002,p,d);
//    cout<<"first ";
//    cout<<MakeConnFull(&d1,&ins, Connections::Standart);
//    cout<<" "<<MakeConnForward(&d1,&ins, Connections::Chain);
//    cout<<"\nsecond"; cout.flush();
//    cout<<" "<<MakeConnFull(&ins,&d2, Connections::Standart);
//    cout<<" "<<MakeConnStrait(&ins,&d2, Connections::Chain);
//    cout<<endl;
//
//    d1.put_material(&m2);
//    cout<<" "<<ins.action()<<endl;
//    ins.action_move();
//    cout<<"Result must be 10:"<<d2.get_material_quantity(m2.getId())<<'\n';
>>>>>>> refs/remotes/origin/main


    Window session_window;
    GUI_C::loadFont("resources/fonts/SpaceGrotesk-Medium.ttf");
    cout<<session_window.GUI.fonts.begin()->getInfo().family;
    session_window.GUI.createButton({0,0},{100,100}, {0,0,0}, {0,0,0}, "lolkek",
                                    []() {std::cout<<"lolkek initiated"<<std::endl;});

    while (session_window.isOpen()) {
        session_window.frame();
    }

//    sf::Font font("resources/fonts/SpaceGrotesk-Medium.ttf");
//    cout<<font.getInfo().family;
    return 0;
}