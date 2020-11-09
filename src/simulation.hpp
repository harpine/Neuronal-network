#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "network.hpp"
#include <fstream>
/*!
  The Simulation class is the main class in this program. It constructs the neuron network System according to user-specified parameters, and @ref run "runs" the simulation.

  A Simulation is made of an object \ref network, which is a vector of pointers to \ref neuron objects. These neurons are constructed with the function \ref add_neurons

  Time (\ref _time) advances from 0 until it reaches \ref T. The state of the network is updated at each time by the \ref run method.

*/
class Simulation {

public : 
    /*!
    Simulation takes the command-line options and extracts the following parameters from them:
        @param _nb the number of neurons in the network
        @param _p_E the percentage of activatory neurons
        @param _time the time until the end of the simulation 
        @param _dt the time step 
        @param _lambda the mean connectivity
        @param _intensity the mean intensity of the connexions
    */
    Simulation(int argc, char** argv);
    Simulation();
    ~Simulation();
    /*!
      @brief run the simulation and return the execution time
      @param dt step time 
      @param time total time of the simulation

      @return the total time of execution
    */
    int run(const double dt, const double time);
    
    void load_config(const std::string &infile);

    void print();

private :
    double _dt, _time;
    Network *_net;
    std::ofstream _outfile;
    
};

#endif //SIMULATION_HPP