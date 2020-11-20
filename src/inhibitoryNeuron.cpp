#include "inhibitoryNeuron.hpp"
#include "random"
//TODO: Add JSON file with config of InhibitoryNeuron


InhibitoryNeuron::InhibitoryNeuron(double delta,std::string type)
:Neuron(type)
{
    double lowerbound(1-delta);
    double upperbound(1+delta);
    if (type=="LTS"){
        _a=0.02*_RNG->uniform_double(lowerbound,upperbound);
        _b=0.25*_RNG->uniform_double(lowerbound,upperbound);
        _c=-65*_RNG->uniform_double(lowerbound,upperbound);
        _d=2*_RNG->uniform_double(lowerbound,upperbound);
        }
    else if (type=="FS"){
        _a=0.1*_RNG->uniform_double(lowerbound,upperbound);
        _b=0.2*_RNG->uniform_double(lowerbound,upperbound);
        _c=-65*_RNG->uniform_double(lowerbound,upperbound);
        _d=2*_RNG->uniform_double(lowerbound,upperbound);
    }
    _v=_c;
    _u=_b*_v;
}

InhibitoryNeuron::~InhibitoryNeuron(){

}
int InhibitoryNeuron::getW() const{
    return 2;
}
int InhibitoryNeuron::factor() const{
    return -1;
}