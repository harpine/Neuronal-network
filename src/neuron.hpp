#ifndef NEURON_HPP
#define NEURON_HPP
#include "random.hpp"


//TODO:Write the body of these methods
class Neuron{
    public:
    Neuron(double a,double b,double c,double d);
    virtual ~Neuron();


    void update();
    void setCurrent(const double current){_current=current;};

    double noise() const {return this->getW() * (_RNG->normal(0,1));};
    bool isFiring();

    virtual int getW() const = 0;
    virtual int factor() const = 0;

    private:
    double _a;
    double _b;
    double _c;
    double _d;
    double _v;
    double _u;
    double _current;
};


#endif //NEURON_HPP