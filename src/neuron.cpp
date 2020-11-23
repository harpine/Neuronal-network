#include "neuron.hpp"
#include "constants.hpp"
#include "random.hpp"

Neuron::Neuron(std::string type)
: _type(type)
{
}

Neuron::~Neuron(){
}
void Neuron::update()
{
    if(isFiring()){
        _v=_c;
        _u+=_d;
    }else{
        _v+=(0.5*(0.04*_v*_v+5*_v+140-_u+_current));
        _v+=(0.5*(0.04*_v*_v+5*_v+140-_u+_current));
        _u+=(_a*(_b*_v-_u));
    }

}

bool Neuron::isFiring(){
    if(_v>=_DISCHARGE_T_){
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