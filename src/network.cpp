#include "network.hpp"
#include <algorithm>
#include "inhibitoryNeuron.hpp"
#include "excitatoryNeuron.hpp"

Network::Network(char model, int nb, double p_E, double intensity, double lambda, double delta)
    : _intensity(intensity), _model(model)
{
    Neuron* neuron;
    int excit(p_E * nb);
    for (int i(0); i < nb - excit; ++i)
    {
        neuron = new InhibitoryNeuron(delta);
        _network.push_back(neuron);
    }
    for (int i(0); i < excit; ++i)
    {
        neuron = new ExcitatoryNeuron(delta);
        _network.push_back(neuron);
    }
    makeConnections(lambda);
}

Network::Network(char model, int nb, double p_FS, double p_IB, double p_RZ, double p_LTS, double p_TC, double p_CH, double intensity, double lambda, double delta)
        : _intensity(intensity), _model(model)
{
    Neuron* neuron;
    std::vector<std::string> type = {"FS", "LTS", "IB", "RZ", "TC", "CH", "RS"};
    int fs(nb*p_FS);
    for (int i(0); i < fs; i++)
    {
        neuron = new InhibitoryNeuron(delta, type[0]);
        _network.push_back(neuron);
    }
    int lts(nb*p_LTS);
    for (int i(0); i < lts; i++)
    {
        neuron = new InhibitoryNeuron(delta, type[1]);
        _network.push_back(neuron);
    }
    int ib(nb*p_IB);
    for (int i(0); i < ib; i++)
    {
        neuron = new ExcitatoryNeuron(delta, type[2]);
        _network.push_back(neuron);
    }
    int rz(nb*p_RZ);
    for (int i(0); i < rz; i++)
    {
        neuron = new ExcitatoryNeuron(delta, type[3]);
        _network.push_back(neuron);
    }
    int tc(nb*p_TC);
    for(int i(0); i < tc; i++) {
        neuron = new ExcitatoryNeuron(delta, type[4]);
        _network.push_back(neuron);
    }
    int ch(nb*p_CH);
    for(int i(0); i < ch; i++) {
        neuron = new ExcitatoryNeuron(delta, type[5]);
        _network.push_back(neuron);
    }

    for (int i(0); i < (nb - fs - lts - ib - rz - tc - ch); i++)
    {
        neuron = new ExcitatoryNeuron(delta, type[6]);
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
    for (size_t i(0); i<_network.size(); i++)
    {
        connections.clear(); //avoid to recreate a new temporary map for each neuron
        int nbConnections;
        if (_model == 'c')
        {
            nbConnections = int(lambda);
        }
        else if(_model == 'o')
        {
            nbConnections = _RNG->poisson(_RNG->exponential(1/lambda));
        }
        else //if another letter is used, we use the basic model
        {
            nbConnections = _RNG->poisson(lambda);
        }
        for (int j(0); j < std::min(nbConnections, int(_network.size())-2) and _connections.size() < _network.size(); j++)
        // we have to take the minimum of both, because the distribution result can be higher than lambda and make an error occuring.
        {
            //pick a random neuron and connect it to the actual neurons. -> using which distribution ??
            size_t k(_RNG->uniform_int(0, _network.size()-1)); //because k is the index, so we have to subtract 1 to the total size
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
            avoidProblem = false;
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
    double input(0);
    for (auto& pair: _connections[index])
    {
        if (pair.first->isFiring())
        {
            input += pair.second;
        }
    }

    _network[index]->setCurrent(_network[index]->noise() + input);

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

std::vector<Neuron*> Network::getNet() const
{
    return _network ;
}
std::vector<std::map<Neuron*, double>> Network::getCon() const
{
    return _connections;
}

Neuron* Network::getInhibitory() const
{
    return _network.front();
}

Neuron* Network::getExcitatory() const
{
    return _network.back();
}

double Network::getValence(int index) const
{
    double input(0);
    for (auto& pair: _connections[index])
    {
            input += pair.second;
    }
    return input;
}