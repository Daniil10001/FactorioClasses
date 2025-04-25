#include "iostream"
#include "interactioninterfaces.hpp"
#include "jsoncommunicate.hpp"
#include "sessionlogic.hpp"
#include<thread>
using std::cout, std::endl;


void printInv(const std::vector<Material>& v)
{
    cout<<" | ";
    for (auto m: v) cout<<"[id: "<<m.getId().id<<", q: "<<m.get_quantity()<<"] ";
    cout<<" | "<<endl;
}


template<class T>
void print_class()
{
    std::cout<<typeid(T).name()<<" "<<typeid(T).hash_code()<<std::endl;
}

int main()
{
    SessionHandler s;
    s.LoadFactory("my.fc");
   /*int i=0;
   while (i<10)
   {
    auto& a=fs->getInventory();
    s.getTims().startHandling(true);
    cout<<"Factory:";printInv(fs->getInventory());
    cout<<"Inserter:";printInv(is->getInventory());
    cout<<"Chest:";printInv(cs->getInventory());  //<<cs->get_material_quantity(ID<>(1))<<' '<<cs->get_material_quantity(ID<>(2))<<'\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
   }*/
   s.SaveFactory("my2.fc");
    return 0;
}