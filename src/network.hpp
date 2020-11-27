#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <vector>
#include <map>
#include <array>
#include "random.hpp"
#include "neuron.hpp"


/**
 * @brief Class that handles the network of neurons.
 * 
 * Network class implement the notion of network, connecting the neurons together and handling the interactions between them.
 * It is defined by a set of neurons and associated connections and intensities, the mean intensity of the connections, a model for the connection
*/

class Network {

public:

/*! @brief Basic constructor.
    Initialize the network by adding the inhibitory & excitatory neurons, given a proportion of excitatory neurons.
    Initialize connection given a model and a mean intensity for the connections.
    @param nb the number of neurons wanted
    @param p_E the proportion of excitatory neurons
    @param intensity the mean intensity of connection
    @param lambda the mean connectivity between neurons
    @param delta the variability around 1 of distribution of noise
    */
Network(char model, int nb, double p_E, double intensity, double lambda, double delta);

/*! @brief Constructor with extended neurons types.
    Initialize the network by adding the neurons, given the different types proportions.
    Initialize connection given a model and a mean intensity for the connections.
    Each type has to be explicitly given, except the type RS, which will be the rest of the neurons.
    @param nb the number of neurons wanted
    @param p_FS the proportion of neurons of type FS
    @param p_IB the proportion of neurons of type IB
    @param p_RZ the proportion of neurons of type RZ
    @param p_LTS the proportion of neurons of type LTS
    @param p_TC the proportion of neurons of type TC
    @param p_CH the proportion of neurons of type CH
    @param intensity the mean intensity of connection
    @param lambda the mean connectivity between neurons
    @param delta the variability around 1 of distribution of noise
    */
Network(char model, int nb, double p_FS, double p_IB, double p_RZ, double p_LTS, double p_TC, double p_CH, double intensity, double lambda, double delta);

/*! @brief Destructor.
  Destroy all neurons in the set
  */
~Network();

/*! @brief Initialize connections.
 * Determine the number of connections for each neuron, given a mean number of connections and depending on the model chosen. 
 * Connect the neurons to the other that will affect their current.
 * @param lambda mean of distribution to know how many connections the neuron will make
*/
void makeConnections(double lambda);

/*! @brief update the neurons.
 * Allows to update all the neurons.
 */
	void update();

/*! @brief Calculate synaptic current received by the neurons.
 * Calculate the synaptic current that the neuron receive and set the current received in the neuron attribute.
 * @param index The index of the neuron on which we want to caculate the total current.
 */
void synapticCurrent(int index);

/*! @brief return a list of 0 & 1, imaging if a vector is firing or not.
 * 0 = hasn't fired this step of time, 1 = fired this step of time
 * @return the list of neurons saying if each neuron is firing (1) or not (0)
 */
 std::vector<bool> getCurrentstatus() const;

 /*! @brief get the list of the neurons in the network
  * @return the list of the neurons composing the networks
  */
  std::vector<Neuron*> getNet() const;

/*! @brief get the list of the connections of neurons in the network
* @return the vector of connections of the network
*/
std::vector<std::map<Neuron*, double>> getCon() const;

/*! @brief Get one neuron of each type and put it in a list  
 * @note The order of the type of neurons is "FS", "LTS", "IB", "RZ", "TC", "CH", "RS"
 * @note If one of the type is not present in the network, the array contains a nullptr at it position.
 * @return An array containing each type of neuron
 */
std::array<Neuron*,7> getNeuronsOutput() const;

/*! @brief get Valence of neuron given in parameters
 * @return the sum of pondered intensity of current
 */
 double getValence(int index) const;


private:
std::vector<Neuron*> _network;
std::vector<std::map<Neuron*, double>> _connections;
double _intensity;
char _model;
std::array<Neuron*,7> _neuronsforoutputs; ///order is FS, LTS, IB, RZ, TC, CH, RS
};

#endif //NETWORK_HPP
