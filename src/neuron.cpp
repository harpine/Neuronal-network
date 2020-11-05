#include "neuron.hpp"
#include "random.hpp"


double Neuron::noise() const
{
    return this->getW() * (_RNG->normal(0,1));
}

void Neuron::update(double dt)
{}

bool Neuron::isFiring()
{
    return 1;
}
bool Neuron::hasFired()
{
    return 1;
}