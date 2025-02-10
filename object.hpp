#ifndef object_hpp__
#define object_hpp__

#define ll long long

struct point
{
    long long x,y;
};


class Object
{
    protected:
        point p;
        bool initilised;
    public:
        Object();
        Object(ll x,ll y);
        void set_cord(ll x,ll y);
        point get_cord();
};


#endif