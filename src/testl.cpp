#include "iostream"
#include "interactioninterfaces.hpp"
#include "jsoncommunicate.hpp"
#include "sessionlogic.hpp"
using std::cout, std::endl;

int main()
{
    cout<<"test Materials\n";
    Material m1=Material(40,1);
    Material m2=Material(10,2);
    Material m3=Material(50,1);

    cout<<m1.get_quantity()<<'\n';
    cout<<"adding BAD and OK\n";
    cout<<ActionResult::BAD<<" "<<ActionResult::OK<<'\n';
    cout<<m1+m2<<" "<<m1+m3<<'\n';
    cout<<m1.get_quantity()<<' '<<m2.get_quantity()<<' '<<m3.get_quantity()<<'\n';
    
    
    cout<< "checking if json works" << endl;
    //
        cout << json_communicate::getNameById(0)<<endl;
        cout << json_communicate::getNameById(1001)<<endl;
        cout<<"test fabric produce\n";

    point<ll> p(0,0);
    Direction d=Direction(Directions::UP);
    Factory f(1001,p,d);
    #if DLEVEL==0
        f.printInventory();
    #endif
    f.produce();
    f.produce();
    f.produce();
    #if DLEVEL==0
        f.printInventory();
    #endif
    cout<<f.get_material_quantity(1)<<'\n';

    Factory f2(1001,p,d);
    Factory f3(1001,p,d);
    Factory f4(1001,p,d);

    cout<<"test connections\n";
    MakeConnFull(&f,&f2, Connections::Standart);
    MakeConnFull(&f4,&f3, Connections::Standart);
    MakeConnFull(&f3,&f2, Connections::Standart);
    MakeConnStrait(&f,&f2, Connections::Chain);

    cout<<"Check connection:\n need to be 0 1 :";
    cout<<f.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
    cout<<"Check connection:\n need to be 1 1 :";
    cout<<f3.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f3.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
    cout<<"Check connection:\n need to be 2 0 :";
    cout<<f2.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f2.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
    
    //dummy and insertion tests
    cout<<"Checking inserters and dummy\n";
    Dummy d1(p), d2(p);
    Inserter ins(1002,p,d);
    cout<<"first";
    cout<<MakeConnFull(&d1,&ins, Connections::Standart);
    cout<<" "<<MakeConnForward(&d1,&ins, Connections::Chain);
    cout<<"\nsecond"; cout.flush();
    cout<<" "<<MakeConnFull(&ins,&d2, Connections::Standart);
    cout<<" "<<MakeConnStrait(&ins,&d2, Connections::Chain);
    cout<<endl;
    
    cout<<"put to dummy "<<d1.put_material(&m2)<<endl;
    ins.setFilt(m2.getId());
    //ins.canDoAction();
    cout<<" "<<ins.action()<<" "<<ins.actionMove()<<endl;
    cout<<"Result must be 1:"<<d2.get_material_quantity(m2.getId())<<'\n';
    cout<<" "<<ins.action()<<" "<<ins.actionMove()<<endl;
    cout<<"Result must be 2:"<<d2.get_material_quantity(m2.getId())<<'\n';
    cout<<" "<<ins.action()<<" "<<ins.actionMove()<<endl;
    cout<<"Result must be 3:"<<d2.get_material_quantity(m2.getId())<<'\n';

    Inserter ins2(1002,p,d);
    MakeConnFull(&d2,&ins2, Connections::Standart);
    MakeConnFull(&ins2,&f2, Connections::Standart);

    MakeConnForward(&d2,&ins2, Connections::Chain);
    MakeConnStrait(&ins2,&f2, Connections::Chain);

    ins2.setFilt(d2.get_material()->getId());
    //ins2.canDoAction();
    cout<<"Must be 0 1 2:"<<ins2.action()<<" "<<ins2.actionMove()<<" "<<d2.get_material()->get_quantity()<<endl;
    
    point<ll> p1(2,2),p2(2,1),p3(2,0);
    Direction dr1(Directions::UP);
    SessionHandler s;

    cout<<"start adding"<<'\n';
    Factory* fs= dynamic_cast<Factory*>(s.addToLayerB(1001,p1,dr1));
    Inserter* is=dynamic_cast<Inserter*>(s.addToLayerB(1002,p2,dr1));
    //std::cout<<is->get_Connection(Connections::Standart)->GetConnectionsTo().size()<<"\n";
    //std::cout<<is->get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<"\n";
    Chest* cs=dynamic_cast<Chest*>(s.addToLayerB(1003,p3,dr1));
    //std::cout<<is->get_Connection(Connections::Standart)->GetConnectionsTo().size()<<"\n";
    //std::cout<<is->get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<"\n";
    //std::cout<<cs->get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<"\n";
    cout<<"end"<<'\n';
    fs->action();
    fs->actionMove();
    cout<<fs->get_material_quantity(ID<>(1))<<'\n';
    cout<<"get "<<(is->action()==ActionResult::OK)<<'\n';
    cout<<"move "<<(is->actionMove()==ActionResult::OK)<<'\n';
    cout<<fs->get_material_quantity(ID<>(1))<<'\n';
    cout<<cs->get_material_quantity(ID<>(1))<<' '<<cs->get_material_quantity(ID<>(2))<<'\n';
    return 0;
}