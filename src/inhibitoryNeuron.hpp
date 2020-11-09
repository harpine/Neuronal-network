#ifndef INHIBITORYNEURON_HPP
#define INHIBITORYNEURON_HPP
#include "neuron.hpp"

/**
 * @brief An inhibitory Neuron class.
 * 
 * A type of neuron inheriting from the pure virtual class Neuron.
 */
class InhibitoryNeuron :public Neuron
{
    public:
    /**
     * @brief Construct a new Inhibitory Neuron object
     * 
     * @param r A random number
     */
    InhibitoryNeuron(double r);
    /**
     * @brief Construct a new Inhibitory Neuron object
     * 
     * @param a describes the time scale of the recovery variable u
     * @param b describes the sensitivity of the recovery variable b.
     * @param c describes the after-spike reset vaue of the membrane potential v.
     * @param d describes the after-spike reset of the recovery variable u.
     */
    InhibitoryNeuron(double a,double b, double c, double d);
    /**
     * @brief Destroy the Inhibitory Neuron object
     * 
     */
    virtual ~InhibitoryNeuron() override;
    /**
     * @brief A getter for the W of the Neuron
     * 
     * @return int the W of the Inhibitory Neuron
     */
    virtual int getW() const override;
    /**
     * @brief A getter for the factor of the Neuron
     * 
     * @return int the factor of the Neuron
     */
    virtual int factor() const override;

};

#endif //INHIBITORYNEURON_HPP