#include <iostream>
#include <random.hpp>
#include "simulation.hpp"
#include "constants.hpp"

Random* _RNG = new Random();

int main(int argc, char** argv){
    Simulation sim(argc, argv);
    sim.run();
    if (_RNG) delete _RNG;
    return 0;
}