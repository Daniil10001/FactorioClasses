#ifndef object_hpp__
#define object_hpp__

#define ll long long

template<typename T> struct point
{
    T x,y;
};


class Object
{
    protected:
        point<ll> p;
        point<unsigned> size;
        bool initilised;
    public:
        Object(ll x,ll y, unsigned x_size, unsigned y_size);
        void set_cord(ll x,ll y);
        point<ll> get_cord();
        point<unsigned> get_size();
};


#endif