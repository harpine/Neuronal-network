#include "inhibitoryNeuron.hpp"
#include <stdexcept>
#include <iostream>
#include "constants.hpp"
//TODO: Add JSON file with config of InhibitoryNeuron


InhibitoryNeuron::InhibitoryNeuron(double delta,std::string type)
:Neuron(type)
{
    double lowerbound(1-delta);
    double upperbound(1+delta);
    try{
    if (type=="LTS"){
        _a=_LTS_A_*_RNG->uniform_double(lowerbound,upperbound);
        _b=_LTS_B_*_RNG->uniform_double(lowerbound,upperbound);
        _c=_LTS_C_*_RNG->uniform_double(lowerbound,upperbound);
        _d=_LTS_D_*_RNG->uniform_double(lowerbound,upperbound);
        }
    else if (type=="FS"){
        _a=_FS_A_*_RNG->uniform_double(lowerbound,upperbound);
        _b=_FS_B_*_RNG->uniform_double(lowerbound,upperbound);
        _c=_FS_C_*_RNG->uniform_double(lowerbound,upperbound);
        _d=_FS_D_*_RNG->uniform_double(lowerbound,upperbound);
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