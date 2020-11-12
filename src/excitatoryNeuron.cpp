#include "excitatoryNeuron.hpp"
#include "random"
//TODO: Add JSON file with config of InhibitoryNeuron


ExcitatoryNeuron::ExcitatoryNeuron(double r)
:Neuron(0.1*(1-0.8*r),0.2*(1+0.25*r),-65,2)
{

}

ExcitatoryNeuron::ExcitatoryNeuron(double a,double b, double c, double d)
:Neuron(a,b,c,d)
{

}


ExcitatoryNeuron::~ExcitatoryNeuron(){

}
int ExcitatoryNeuron::getW() const{
    return 5;
}
int ExcitatoryNeuron::factor()const{
    return 1;
}