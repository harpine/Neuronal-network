#include "inhibitoryNeuron.hpp"
#include <stdexcept>
#include <iostream>
//TODO: Add JSON file with config of InhibitoryNeuron


InhibitoryNeuron::InhibitoryNeuron(double delta,std::string type)
:Neuron(type)
{
    double lowerbound(1-delta);
    double upperbound(1+delta);
    try{
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
    }else{
       throw std::domain_error("There is no neuron"); 
    }
    }catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
    }
}

InhibitoryNeuron::~InhibitoryNeuron(){

}
int InhibitoryNeuron::getW() const{
    return 2;
}
int InhibitoryNeuron::factor() const{
    return -1;
}