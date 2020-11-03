#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "network.hpp"
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
    Simulation(int, char**);
    ~Simulation();
    /*!
      Run the simulation at _delta_t interval
    */
    void run(const double dt, const double time);
    
    void load_config(const std::string &infile);

private :
    double _dt, _time;
    Network net;
    
}

#endif //SIMULATION_HPP