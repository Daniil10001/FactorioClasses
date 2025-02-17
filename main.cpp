#include "iostream"
#include "material.hpp"
#include "interactioninterfaces.hpp"
#include "factory.hpp"
using std::cout;

int main()
{
    Material m1=Material(40,1);
    Material m2=Material(10,2);
    Material m3=Material(50,1);

    cout<<m1.get_quantity()<<'\n';
    cout<<"adding BAD and OK\n";
    cout<<ActionResult::BAD<<" "<<ActionResult::OK<<'\n';
    cout<<m1+m2<<" "<<m1+m3<<'\n';
    cout<<m1.get_quantity()<<' '<<m2.get_quantity()<<' '<<m3.get_quantity()<<'\n';
    point<ll> p;
    p.x=0;
    p.y=0;
    Factory f(1,1001,p);
    
    f.proceed();
    cout<<f.get_material_quantity(1)<<'\n';
    return 0;
}