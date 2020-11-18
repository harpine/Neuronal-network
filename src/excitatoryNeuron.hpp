#ifndef EXCITATORYNEURON_HPP
#define EXCITATORYNEURON_HPP
#include "neuron.hpp"

/**
 * @brief An excitatory Neuron class.
 * 
 * A type of neuron inheriting from the pure virtual class Neuron.
 */
class ExcitatoryNeuron :public Neuron
{
    public:
    /**
     * @brief Construct a new Excitatory Neuron object
     * 
     * @param r A random number
     */
    ExcitatoryNeuron(double r,std::string type="RS");
    /**
     * @brief Construct a new Excitatory Neuron object
     * 
     * @param a describes the time scale of the recovery variable u
     * @param b describes the sensitivity of the recovery variable b.
     * @param c describes the after-spike reset vaue of the membrane potential v.
     * @param d describes the after-spike reset of the recovery variable u.
     */
    ExcitatoryNeuron(double a,double b, double c, double d);
    /**
     * @brief Destroy the Excitatory Neuron object
     */
    virtual ~ExcitatoryNeuron() override;
    /**
     * @brief A getter for the W of the Neuron
     * 
     * @return int the W of the Excitatory Neuron
     */   
    virtual int getW() const override;
    /**
     * @brief A getter for the factor of the Neuron
     * 
     * @return int the factor of the Excitatory Neuron
     */
    virtual int factor() const override;

};

#endif //EXCITATORYNEURON_HPP