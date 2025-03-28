#include "iostream"
#include "material.hpp"
#include "interactioninterfaces.hpp"
#include "factory.hpp"
#include "jsoncommunicate.hpp"
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
    cout<<"test fabric produce\n";
    point<ll> p;
    Factory f(1001,p,Direrctions::UP);
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

    Factory f2(1001,p,Direrctions::UP);
    Factory f3(1001,p,Direrctions::UP);
    Factory f4(1001,p,Direrctions::UP);

    cout<<"test connections\n";
    MakeConnection(&f,&f2, Connections::Standart);
    MakeConnection(&f4,&f3, Connections::Standart);
    MakeConnection(&f3,&f2, Connections::Standart);

    cout<<"Check connection:\n need to be 0 1 :";
    cout<<f.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
    cout<<"Check connection:\n need to be 1 1 :";
    cout<<f3.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f3.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
    cout<<"Check connection:\n need to be 2 0 :";
    cout<<f2.get_Connection(Connections::Standart)->GetConnectionsFrom().size()<<' '<<f2.get_Connection(Connections::Standart)->GetConnectionsTo().size()<<'\n';
    

   cout<< "checking if json works" << endl;
//
    cout << json_communicate::getNameById(0)<<endl;
    //cout << json_communicate::getNameById(0);


    return 0;
}