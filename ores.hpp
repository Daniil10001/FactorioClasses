#ifndef ores_hpp__
#define ores_hpp__

class Ore: public Material {
protected:
    int defaultMiningSpeed;
private:
    virtual void getMiningSpeed(int k) = 0;
};

class IronOre: public Material {};

class CopperOre: public Material {};

class Stone: public Material {};



#endif