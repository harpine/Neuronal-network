#include "network.hpp"
#include <map>
#include <algorithm>
#include "inhibitoryNeuron.hpp"
#include "excitatoryNeuron.hpp"
#include <iostream>

Network::Network(int nb, double p_E, double intensity, double lambda)
    : _intensity(intensity)
{
    Neuron* neuron;
    for (int i(0); i < nb; ++i)
    {
        if(_RNG->bernoulli(p_E))
        {
            neuron = new InhibitoryNeuron(_RNG->normal(0,1));
        }
        else
        {
            neuron = new ExcitatoryNeuron(_RNG->normal(0,1));
        }
        _network.push_back(neuron);
    }
    makeConnections(lambda);
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
    std::map<Neuron*, double> connections;
    bool avoidProblem(false);
    std::cerr << _network.size();
    for (size_t i(0); i<_network.size(); i++)
    {
        connections.clear(); //avoid to recreate a new temporary map for each neuron
        for (int j(0); j < _RNG->poisson(lambda) and _connections.size()< _network.size(); j++)
        {
            //pick a random neuron and connect it to the actual neurons. -> using which distribution ??
            size_t k(_RNG->uniform_int(0, _network.size()-1)); //because k is the index, so we have to substract 1 to the total size
            while (connections.find(_network[k]) != connections.end() or k == i) //avoid to have 2 times the same neuron
            {
                k+=1; //isn't really random, but can avoid to repeat thousands of time the uniform distribution.
                if (k > _network.size()-1)
                {
                    if (avoidProblem)
                    {
                       throw std::domain_error ("this neuron is already connected to all neurons of the network");
                    }
                    k= 0;
                    avoidProblem = true;
                }
            }

            connections.insert(std::make_pair(_network[k], _network[i]->factor() * _RNG->uniform_double(0, 2*_intensity)));
        }
        _connections.push_back(connections);
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
        status.push_back(_network[i]->isFiring());
    }
    return status;
}


