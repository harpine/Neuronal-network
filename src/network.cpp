#include "network.hpp"
#include <map>
#include <algorithm>
#include "inhibitoryNeuron.hpp"
#include "excitatoryNeuron.hpp"

Network::Network(int nb, double p_E, double intensity, double lambda)
    : _intensity(intensity)
{
    Neuron* neuron;
    for (int i(0); i < nb; ++i)
    {
        if(_RNG->bernoulli(p_E))
        {
            neuron = new InhibitoryNeuron(_RNG->normal(0,1)); // TODO: existe plus du tout ?
        }
        else
        {
            neuron = new ExcitatoryNeuron(_RNG->normal(0,1)); //TODO: existe plus du tout? 
        }
        _network.push_back(neuron);
    }
    makeConnections(lambda);
}

Network::Network(std::vector<std::vector<double>> parameters, double intensity, double lambda)
    :_intensity(intensity)
{
    Neuron* neuron;
    for (size_t i(0); i < parameters.size(); i++)
    {
        if (parameters[i][0] == 0) {
            neuron = new InhibitoryNeuron(parameters[i][1], parameters[i][2], parameters[i][3], parameters[i][4]);
        }
        if (parameters[i][0] == 1) {
            neuron = new ExcitatoryNeuron(parameters[i][1], parameters[i][2], parameters[i][3], parameters[i][4]);
        }
    }

    _network.push_back(neuron);


}

Network::~Network()
{
    for (auto& neuron: _network)
    {
        delete neuron;
        neuron = nullptr;
    }
}
void Network::makeConnections(double lambda)
{
    bool avoidProblem(false);
    std::map<Neuron*, double> connections;
    for (size_t i(0); i<_network.size(); i++)
    {
        connections.clear(); //avoid to recreate a new temporary map for each neuron
        for (int j(0); j < _RNG->poisson(lambda); j++)
        {
            //pick a random neuron and connect it to the actual neurons. -> using which distribution ??
            size_t k(_RNG->uniform_int(0, _network.size()));
            while (connections.find(_network[k]) != connections.end() or k == i) //avoid to have 2 times the same neuron
            {
                
                k+=1; //isn't really random, but can avoid to repeat thousands of time the uniform distribution.
                if (k>= _network.size())
                {
                    k=0;
                    if (avoidProblem)
                    {
                        throw std::domain_error("This neuron is already connected to all other neurons of the network.");
                    }
                    avoidProblem = true;
                }
            }
            connections.insert(std::make_pair(_network[k], _network[i]->factor() * _RNG->uniform_double(0, 2*_intensity)));
        }
        _connections[i] = connections;
    }
}

void Network::update()
{
    for (size_t i(0); i <_network.size(); i++)
    {
        synapticCurrent(i);
        _network[i]->update();
    }
}

void Network::synapticCurrent(int index)
{
    //TODO: pas fait exactement comme dans la donnée, j'ai l'impression que c'est mieux???
    //std:map<Neuron*, double> excitatory;
    //std:map<Neuron*, double> inhibitory;
    double excitatoryInput(0);
    double inhibitoryInput(0);
    for (auto& pair: _connections[index])
    {
        if (pair.first->isFiring())
        {
            if (pair.second > 0) // so it is an excitatory neuron
            {
                excitatoryInput += 0.5 *(pair.second);
                //excitatory.insert(pair);
            }
            else
            {
                inhibitoryInput += pair.second; // we add negative values
                //inhibitory.insert(pair);
            }
        }
    }

    _network[index]->setCurrent(_network[index]->noise() + excitatoryInput + inhibitoryInput);

    // double excitatoryInput(0);

    // for (auto pair: excitatory)
    // {
    //         excitatoryInput += pair->second;
    // }
    // double inhibitoryInput(0);
    // for (auto neuron: inhibitory)
    // {
    //     inhibitoryInput += pair->second;
    // }
    //return (neuron.noise() + 0.5 * excitatoryInput - inhibitoryInput);
}

std::vector<bool> Network::getCurrentstatus() const
{
    std::vector<bool> status;
    for (size_t i(0); i < _network.size(); i++)
    {
        status[i] = _network[i]->isFiring();
    }
    return status;
}


