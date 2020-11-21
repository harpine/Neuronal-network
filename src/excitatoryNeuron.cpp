#include "excitatoryNeuron.hpp"
#include "random.hpp"
#include <stdexcept>
#include <iostream>
#include "constants.hpp"
//TODO: Add JSON file with config of InhibitoryNeuron


ExcitatoryNeuron::ExcitatoryNeuron(double delta,std::string type)
:Neuron(type)
{
    try{
    double lowerbound(1-delta);
    double upperbound(1+delta);
    if (type=="RS"){
        _a=_RS_A_*_RNG->uniform_double(lowerbound,upperbound);
        _b=_RS_B_*_RNG->uniform_double(lowerbound,upperbound);
        _c=_RS_C_*_RNG->uniform_double(lowerbound,upperbound);
        _d=_RS_D_*_RNG->uniform_double(lowerbound,upperbound);
        }
    else if (type=="IB"){
        _a=_IB_A_*_RNG->uniform_double(lowerbound,upperbound);
        _b=_IB_B_*_RNG->uniform_double(lowerbound,upperbound);
        _c=_IB_C_*_RNG->uniform_double(lowerbound,upperbound);
        _d=_IB_D_*_RNG->uniform_double(lowerbound,upperbound);
        }
    else if (type=="CH"){
        _a=_CH_A_*_RNG->uniform_double(lowerbound,upperbound); 
        _b=_CH_B_*_RNG->uniform_double(lowerbound,upperbound);
        _c=_CH_C_*_RNG->uniform_double(lowerbound,upperbound);
        _d=_CH_D_*_RNG->uniform_double(lowerbound,upperbound);
        }
    else{
       throw std::domain_error("There is no "+type+" neuron"); 
    }
    }catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
    }

}


ExcitatoryNeuron::~ExcitatoryNeuron(){

}
int ExcitatoryNeuron::getW() const{
    return 5;
}
int ExcitatoryNeuron::factor()const{
    return 1;
}