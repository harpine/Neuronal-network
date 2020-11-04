#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <vector>
#include <map>
#include "random.hpp"
#include "neuron.hpp"


/*! @brief class that handles the network of neurons.
    Network class implement the notion of network, connecting the neurons together and handling the interactions between them.
    it is defined bya set of neurons and the mean intensity of the connections
*/

class Network {

public:

/*! @brief Constructor.
    initialize the network by adding the neurons
    @param nb number of neurons wanted
    @param p_E proportionality of excitatory neurons
    @param intensity mean intensity of connection
    @param lambda mean connectivity between neurons
    */
Network(int nb, double p_E, double intensity, double lambda);
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
	void update(const double dt); 
/*!
  @brief calculate synaptic current received by the neurons.
  calculate the synaptic current that the neuron receive and set the current received in the neuron attribute.
  @param neuron the neuron on which we want to caculate the total current.
 */
	void synapticCurrent(Neuron* neuron);

private:
/*!
 collection of neurons that are in the network
 */
std::vector<Neuron*> _network;
// /*! mean connectivity between neurons -> to use with Poisson distribution
// */
// double _lambda;
//TODO: pas besoin en attribut non?
/*! collection of connections to the neurons of corresponding index.
*/
std::vector<std::map<Neuron*, double>> _connections;

/*! mean intensity of connexions between connexions
*/
double _intensity;
}

#endif //NETWORK_HPP
