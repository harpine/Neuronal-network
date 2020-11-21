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
     * @param delta The delta of uniform distribution determining the noise 
     */
    ExcitatoryNeuron(double delta,std::string type="RS");
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