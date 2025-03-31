#ifndef object_hpp__
#define object_hpp__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"interactioninterfaces.hpp"

class Object
{
    protected:
        unsigned id;
        point<ll> p;
        point<unsigned> size;
        bool initilised;
        //sf::Sprite sprie;
    public:
        Object():initilised(0){};
        Object(ll x,ll y, unsigned x_size, unsigned y_size);
        Object(unsigned id);
        virtual ~Object();
        void set_cord(ll x,ll y);
        const point<ll>& get_cord();
        const point<unsigned>& get_size();
};


#endif