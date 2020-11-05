#include "inhibitoryNeuron.hpp"
#include "random"
//TODO: Add JSON file with config of InhibitoryNeuron


InhibitoryNeuron::InhibitoryNeuron(double r)
:Neuron(0.02,0.2,-65*(1-(1/13))*r*r,8*(1-(3/4))*r*r)
{

}

InhibitoryNeuron::~InhibitoryNeuron(){

}
int InhibitoryNeuron::getW() const{
    return 2;
}
int InhibitoryNeuron::factor() const{
    return -1;
}