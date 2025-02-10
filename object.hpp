#ifndef object_hpp__
#define object_hpp__

class Object
{
    protected:
        long long x,y;
        bool initilised;
    public:
        Object();
        Object(int x,int y);
        void set_cord(int x,int y);
};


#endif