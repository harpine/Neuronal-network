#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "network.hpp"
#include <fstream>
#include <time.h>

/*!
  The Simulation class is the main class in this program. It constructs the neuron network System according to user-specified parameters, and @ref run "runs" the simulation.

  A Simulation is made of an object \ref network, which is a vector of pointers to \ref neuron objects. These neurons are constructed with the function \ref add_neurons

  Time (\ref _time) advances from 0 until it reaches \ref T. The state of the network is updated at each time by the \ref run method.

*/
class Simulation {

public : 
    /*!
    @brief Simulation takes the command-line options and extracts the following parameters from them:
        @param _nb the number of neurons in the network
        @param _p_E the percentage of activatory neurons
        @param _time the time until the end of the simulation 
        @param _dt the time step 
        @param _lambda the mean connectivity
        @param _intensity the mean intensity of the connexions
        @param _model the model chosen for the connections
        @param _delta a tunable parameter for neuron noise
        @param _rep the repartition of under categories of neurons
    */
    Simulation(int argc, char** argv);
    Simulation(std::string outfile);
    ~Simulation();

    /*!
      @brief run the simulation and return the execution time.
      @param dt step time 
      @param time total time of the simulation

      @return the total time of execution
    */
    int run(const double dt);

/*!
      @brief write into the output stream the status of each neuron in the network for every step of time.
    */
    void print(int index);

/*! @brief write into new file status of the parameters for each neuron.
   */ 
    void testParamPrint();

/*! @brief write into new file the v, u and intensity of one inhibitory and one excitatory neuron for each step of time.
   */ 
    void testSamplePrint();

/*! @brief read the line passed as argument and affects value if finds corresponding value
    @param line from what we can extract informations
    @param fs, ib, rz, lts proportions of neurons initialized to zero and updated if contained in the line

    can throw logic error if sum of all proportions greater than 1
   */ 
    void readLine(std::string& line, double& fs, double& ib, double& rz, double& lts);

private :
    double _dt, _time;
    Network *_net;
    std::ofstream _outfile;
    bool _options;
};

#endif //SIMULATION_HPP