#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "network.hpp"
#include <fstream>
#include <time.h>

/*!
  @brief The \ref Simulation class is the main class in this program. It constructs the neuron network System according to user-specified parameters, and @ref run "runs" the simulation.
  A \ref Simulation is made of an object network, which is a vector of pointers to neuron objects. These neurons are constructed with the function add_neurons.
  Time (\ref _time) advances from 0 until it reaches T. The state of the network is updated at each time by the \ref run method.

*/
class Simulation {

public : 
    /*!
    @brief Simulation takes the command-line options and extracts the following parameters from them:
        @param _nb the number of neurons in the network (an int)
        @param _p_E the percentage of activatory neurons (a double)
        @param _time the time until the end of the simulation (an int)
        @param _lambda the mean connectivity (a double)
        @param _intensity the mean intensity of the connexions (a double)
        @param _model the model chosen for the connections (a char)
        @param _delta a tunable parameter for neuron noise (a double)
        @param _rep the repartition of under categories of neurons (a string)
    */
    Simulation(int argc, char** argv);

    /*! @brief Creates a new object Simulation using default parameters and a outfile given.
    * @param outfile the outfile for the output
    */
    Simulation(const std::string& outfile);

    /*! @brief Destructor.
  Destroy the _network attribute
  */
    ~Simulation();

    /*!
      @brief Run the simulation and return the execution time.
      Use attribute _dt as step of time for the simulation.
      @return the total time of execution
    */
    int run();

/*!
      @brief Write into the output stream the status of each neuron in the network for every step of time.
    */
    void print(int index);

/*! @brief Write into a new file status of the parameters for each neuron.
   */ 
    void paramPrint();

/*! @brief Write into a new file the v, u and intensity of one inhibitory and one excitatory neuron for each step of time.
    @param file the outfile
   */ 
    void samplePrint(std::ofstream& file);

/*! @brief Read the line passed as argument and affects value if finds corresponding value
    @param line from what we can extract informations
    @param fs, ib, rz, lts, tc, ch proportions of neurons initialized to zero and updated if contained in the line

    @note Can throw logic error if sum of all proportions greater than 1
   */ 
    void readLine(std::string& line,  double& fs, double& ib, double& rz, double& lts, double& tc, double& ch);

    /*! @brief Initialisation of file samples.
     * @param p_E proportion of excitatory Neurons
     */
    void initializeSample(double p_E);

    /*! @brief Initialisation of file samples.
     * @param p_FS proportion of FS Neurons
     * @param p_LTS proportion of LTS Neurons
     * @param p_IB proportion of IB Neurons
     * @param p_RZ proportion of RZ Neurons
     * @param p_TC proportion of TC Neurons
     * @param p_CH proportion of CH Neurons
 */
    void initializeSample(double p_FS, double p_LTS, double p_IB, double p_RZ, double p_TC, double p_CH);

private :
    double _dt, _time;
    Network *_net;
    std::ofstream _outfile;
    std::string _filename;
    bool _options;
};

#endif //SIMULATION_HPP