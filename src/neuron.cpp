#include "neuron.hpp"
#include "constants.hpp"



Neuron::Neuron(double a,  double b, double c, double d)
: _a(a),_b(b),_c(c),_d(d)
{
    _v=-65;
    _u=_b*_v;
}

Neuron::~Neuron(){

}
void Neuron::update()
{
    if(isFiring()){
        _v=_c;
        _u=_u+_d;
    }else{
        _v+=0.5*(0.04*_v*_v+5*_v+140-_u+_current);
        _v+=0.5*(0.04*_v*_v+5*_v+140-_u+_current);
        _u+=_a*(_b*_v-_u);
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
