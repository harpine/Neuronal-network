#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <vector>
#include <map>
#include "random.hpp"
#include "neuron.hpp"


/*! @brief class that handles the network of neurons.
    Network class implement the notion of network, connecting the neurons together and handling the interactions between them.
    it is defined by a set of neurons and the mean intensity of the connections
*/

class Network {

public:

/*! @brief Basic constructor.
    initialize the network by adding the inhibitory & excitatory neurons, given a proportion of inhibitory neurons.
    @param nb the number of neurons wanted
    @param p_E the proportion of excitatory neurons
    @param intensity the mean intensity of connection
    @param lambda the mean connectivity between neurons
    @param delta the variability of distribution of noise TODO: find better definition
    */
Network(char model, int nb, double p_E, double intensity, double lambda, double delta);

/*! @brief Constructor with extended neurons types.
    initialize the network by adding the neurons, given the different types proportions.
    Each type has to be explicitly given, except the type RS, which will be the rest of the neurons.
    @param nb the number of neurons wanted
    @param p_FS the proportion of neurons of type FS
    @param p_IB the proportion of neurons of type IB
    @param p_RZ the proportion of neurons of type RZ
    @param p_LTS the proportion of neurons of type LTS
    @param intensity the mean intensity of connection
    @param lambda the mean connectivity between neurons
    @param delta the variability of distribution of noise TODO: find better definition
    */
Network(char model, int nb, double p_FS, double p_IB, double p_RZ, double p_LTS, double intensity, double lambda, double delta);

/*! @brief Destructor.
  Destroy all neurons in the set*/
~Network();

/*! @brief initialize connections.
 determine the number of connections, given a mean number of conections.
 Connect the neurons together.
 @param lambda mean of distribution to know how many connections the neuron will make
*/
void makeConnections(double lambda);
/*! @brief update the neurons.
 * Allows to update all the neurons of the network by step of time
 @param dt the time step
 */
	void update();
/*!
  @brief calculate synaptic current received by the neurons.
  calculate the synaptic current that the neuron receive and set the current received in the neuron attribute.
  @param neuron the neuron on which we want to caculate the total current.
  @return the intensity of the current on the neuron of index given.
 */
	double synapticCurrent(int index);

	/*! @brief return a list of 0 & 1, imaging if a vector is firing or not.
	 * 0 = hasn't fired this step of time, 1 = fired this step of time
	 * @return the list of neurons saying, if each neuron is firing (1) or not (0)
	 */
	 std::vector<bool> getCurrentstatus() const;

	 /*! @brief get the list of the neurons in the network
	  * @return the network
	  */
	  std::vector<Neuron*> getNet() const;
    /*! @brief get the list of the neurons in the network
    * @return the vector of connections of the network
    */
    std::vector<std::map<Neuron*, double>> getCon() const;
    /*! @brief get the 1st neuron, that is an inhibitory one
     * @return the pointer on the first neuron
     */
    Neuron* getInhibitory() const;
    /*! @brief get the last neuron, that is an inhibitory one
    * @return the pointer on the last neuron
    */
    Neuron* getExcitatory() const;

private:
/*!
 collection of neurons that are in the network
 */
std::vector<Neuron*> _network;

/*! collection of connections to the neurons of corresponding index.
*/
std::vector<std::map<Neuron*, double>> _connections;

/*! mean intensity of connexions between connexions
*/
double _intensity;

/*! name of model used for connections: basic, constant or overdispersed
 */
 char _model;
};

#endif //NETWORK_HPP
