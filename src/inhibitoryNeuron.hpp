#ifndef INHIBITORYNEURON_HPP
#define INHIBITORYNEURON_HPP
#include "neuron.hpp"


class InhibitoryNeuron :public Neuron
{
    public:
    InhibitoryNeuron(double r);
    virtual int getW() const override;
    virtual int factor() const override;
    virtual ~InhibitoryNeuron() override;
};

#endif //INHIBITORYNEURON_HPP