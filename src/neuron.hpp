#ifndef NEURON_HPP
#define NEURON_HPP
#include <map>


//TODO:Write the body of these methods
class Neuron{
    public:
    Neuron(double a,double b,double c,double d);
    
    double noise();
    void update(double dt);
    void setCurrent(const double current){_current=current};

    bool isFiring();
    bool hasFired();
    int getW()=0 const;
    int factor()=0 const;

    private:
    double _a;
    double _b;
    double _c;
    double _d;
    double _current;
    bool _isfiring;
    std::map<Neuron*,double> _connections;
}


#endif //NEURON_HPP