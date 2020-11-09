#include <iostream>
#include <random.hpp>
#include "simulation.hpp"
#include "constants.hpp"

Random* _RNG;

int main(int argc, char** argv){
    Simulation sim(argc, argv);
    sim.run(_DELTA_T_);
    sim.print();
    return 0;
}