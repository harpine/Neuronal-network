#ifndef INHIBITORYNEURON_HPP
#define INHIBITORYNEURON_HPP
#include "neuron.hpp"


class ExcitatoryNeuron :public Neuron
{
    public:
    ExcitatoryNeuron(double r);
    virtual int getW() const override;
    virtual int factor() const override;
    virtual ~ExcitatoryNeuron() override;
};

#endif //INHIBITORYNEURON_HPP