#include "neuron.hpp"
#include "constants.hpp"
#include "random.hpp"

Neuron::Neuron(std::string type)
: _current(0.0), _type(type)
{
}

Neuron::~Neuron(){
}
void Neuron::update()
{
    double tmp_v(_v);
    double tmp_u(_u);
    if(isFiring()){
        _v=_c;
        _u+=_d;
    }else{
        _v+=(0.5*(0.04*tmp_v*tmp_v+5*tmp_v+140-tmp_u+_current));
        _v+=(0.5*(0.04*tmp_v*tmp_v+5*tmp_v+140-tmp_u+_current));
        _u+=(_a*(_b*tmp_v-tmp_u));
    }
}

bool Neuron::isFiring(){
    if(_v>=_DISCHARGE_T_){
        _v=_DISCHARGE_T_;
        return true;
    }
    return false;
}
std::vector<double> Neuron::getAttributs(){
    return {_a,_b,_c,_d};
}
std::vector<double> Neuron::getVariables(){
    return {_v,_u, _current};
}
std::string Neuron::getType() const{
    return _type;
} 