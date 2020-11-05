#ifndef NEURON_HPP
#define NEURON_HPP
#include <map>


//TODO:Write the body of these methods
class Neuron{
    public:
    Neuron(double a,double b,double c,double d);
    virtual ~Neuron();
    double noise() const;
    void update(double dt);
    void setCurrent(const double current){_current=current;};

    bool isFiring();
    bool hasFired();
    virtual int getW() const =0;
    virtual int factor() const =0;

    private:
    double _a;
    double _b;
    double _c;
    double _d;
    double _current;
    bool _isfiring;
    std::map<Neuron*,double> _connections;
};


#endif //NEURON_HPP