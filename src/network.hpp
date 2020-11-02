#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <vector>
#include "Random.hpp"
#include "Neuron.hpp"

class Neuron; 

class Network {

public:
/*! Constructor */
Network(std::vector<Neuron*> network, double lambda);
/*! Destructor, to destroy all neurons*/
~Network();
/*! connect the neurons together
 @param lambda mean of distribution to know how many connections the neuron will make
*/
void makeConnections(double lambda);
/*! 
 * Allows to update all the neurons of the network.
 @param dt the time step
 */
	double update(const double dt); 
/*!
  calculate the synaptic current that the neuron becomes and set the current received in the neuron attribute.
  @param neuron the neuron on which we want to caculate the total current.
 */
	void synapticCurrent(Neuron* neuron);

private:
/*!
 collection of neurons that are in the network
 */
std::vector<Neuron*> _network;
// /*! mean connectivity between neurons -> to use with Pois distribution
// */
// double _lambda;
// ?? pas besoin en attribut non?

/*! mean intensity of connexions between connexions
*/
double _intensity;
}

#endif //NETWORK_HPP
