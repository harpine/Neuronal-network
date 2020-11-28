#include <iostream>
#include <random.hpp>
#include "simulation.hpp"
#include "constants.hpp"
#include <ctime>

Random* _RNG = new Random();

int main(int argc, char** argv){
    try{
        clock_t init, final;
        init = clock();
        Simulation sim(argc, argv);
        sim.run();
        final = clock();
        std::cerr << final - init << std::endl;
        if (_RNG) delete _RNG;
    } catch (const std::exception &e) {
        return 1;
    }
    return 0;
}