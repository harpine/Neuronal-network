#include <iostream>
#include <random.hpp>
#include "simulation.hpp"
#include "constants.hpp"

Random* _RNG = new Random();

int main(int argc, char** argv){
    //Simulation sim(argc, argv);
    //sim.run(_DELTA_T_);
    Simulation sim(_OUTFILE_);
    sim.run(_DELTA_T_);
    sim.read_file(_OUTFILE_);
    if (_RNG) delete _RNG;
    return 0;
}