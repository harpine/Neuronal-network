#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "network.hpp"
#include <fstream>
#include <time.h>

/*!
  * @brief storage of neuron parameters when given by a configuration.
  * 
  * @param type indicates if the neuron is excitatory (1) or inhibitory (0).
  * @param a describes the time scale of the recovery variable u
  * @param b describes the sensitivity of the recovery variable b.
  * @param c describes the after-spike reset vaue of the membrane potential v.
  * @param d describes the after-spike reset of the recovery variable u.
*/
struct Param {
  std::string type;
  double a;
  double b;
  double c;
  double d;
  double inhibitory;
  double valence;
  double degree;
};

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

    void testParamPrint();
    void testSamplePrint();

private :
    double _dt, _time;
    Network *_net;
    std::ofstream _outfile;

    void readLine(std::string& line, double& fs, double& ib, double& rz, double& lts);
};

#endif //SIMULATION_HPP