#include "excitatoryNeuron.hpp"
#include "random"
//TODO: Add JSON file with config of InhibitoryNeuron


ExcitatoryNeuron::ExcitatoryNeuron(double delta,std::string type)
:Neuron(type)
{
    double lowerbound(1-delta);
    double upperbound(1+delta);
    if (type=="RS"){
        _a=0.02*_RNG->uniform_double(lowerbound,upperbound);
        _b=0.2*_RNG->uniform_double(lowerbound,upperbound);
        _c=-65*_RNG->uniform_double(lowerbound,upperbound);
        _d=8*_RNG->uniform_double(lowerbound,upperbound);
        }
    else if (type=="IB"){
        _a=0.02*_RNG->uniform_double(lowerbound,upperbound);
        _b=0.2*_RNG->uniform_double(lowerbound,upperbound);
        _c=-55*_RNG->uniform_double(lowerbound,upperbound);
        _d=4*_RNG->uniform_double(lowerbound,upperbound);
        }
    else if (type=="CH"){
        _a=0.02*_RNG->uniform_double(lowerbound,upperbound);
        _b=0.2*_RNG->uniform_double(lowerbound,upperbound);
        _c=-50*_RNG->uniform_double(lowerbound,upperbound);
        _d=2*_RNG->uniform_double(lowerbound,upperbound);
        }
    _v=_c;
    _u=_b*_v;
}


ExcitatoryNeuron::~ExcitatoryNeuron(){

}
int ExcitatoryNeuron::getW() const{
    return 5;
}
int ExcitatoryNeuron::factor()const{
    return 1;
}