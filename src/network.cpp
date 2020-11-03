#include "network.hpp"
#include <map>
#include <iostream>

Network::Network(int nb, double p_E, double intensity, double lambda)
    : _intensity(intensity)
{
    Neuron* neuron;
    for (int i(0); i < nb; ++i)
    {
        if(bernoulli(p_E))
        {
            neuron = new InhibitoryNeuron();
        }
        else
        {
            neuron = new ExcitatoryNeuron();
        }
         //?? arguments à adapter selon constructeur
        _network.push_back(neuron);
    }
    try{
    makeConnections(lambda);
    }catch(std::domain_error& e){
        std::cerr << e.what();
    }
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
    std::map<Neuron* , double> connections;
    for (auto& neuron : _network)
    {
        connections.erase(); //avoid to recreate a new temporary map for each neuron
        for (int i(0); i < _RNG->poisson(lambda); i++)
        {
            //pick a random neuron and connect it to the actual neurons. -> using which distribution ??
            int j(uniform_int(0, _network.size()));
            while (connections.find(_network[j]) != connections.end() or _network[j] == neuron) //avoid to have 2 times the same neuron
            {
                
                j+=1; //isn't really random, but can avoid to repeat thousands of time the uniform distribution.
                if (j>= _network.size())
                {
                    j=0;
                    if (avoidProblem)
                    {
                        throw std::domain_error("This neuron is already connected to all other neurons of the network.");
                    }
                    avoidProblem = true;
                }
            }
            connections.insert{_network[j], neuron->factor() * uniform_int(0, 2*_intensity)};
        }
        neuron->makeConnections(connections);
    }
}

void Network::update(double dt)
{
    for (auto neuron: _network)
    {
        neuron->update(dt);
    }
}

void Network::synapticCurrent(Neuron* neuron)
{
    // pas fait exactement comme dans la donnée, j'ai l'impression que c'est mieux???
    //std:map<Neuron*, double> excitatory;
    //std:map<Neuron*, double> inhibitory;
    double excitatoryInput(0);
    double inhibitoryInput(0);
    for (auto& pair: neuron.getConnections())
    {
        if (pair->first->is_firing())
        {
            if (pair->second > 0) // so it is an excitatory neuron
            {
                excitatoryInput += 0.5 *(pair->second);
                //excitatory.insert(pair);
            }
            else
            {
                inhibitoryInput += pair->second; // we add negative values
                //inhibitory.insert(pair);
            }
            pair->first->has_fired();
        }
    }

    neuron->setSynapticCurrent(neuron->makeNoise() + excitatoryInput + inhibitoryInput);

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
    //return (neuron.makeNoise() + 0.5 * excitatoryInput - inhibitoryInput);
}