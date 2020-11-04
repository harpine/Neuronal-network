#include "neuron.hpp"



double MakeNoise()
{
	return this→getW() * (_RNG.normal(0,1)) ;
}
