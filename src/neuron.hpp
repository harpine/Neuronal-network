#ifndef NEURON_HPP
#define NEURON_HPP
#include "random.hpp"



/**
 * @brief A pure virtual class Neuron.
 * 
 * Class defined by 4 dimensionless parameters a,b,c,d. 
 * 2 systems of ordinary differential equaitons of who's variables are v,u 
 * and the current from the network it belongs to.
 * 
 */
class Neuron{
    public:
    /**
     * @brief Construct a new Neuron object
     * 
     * @param a describes the time scale of the recovery variable u
     * @param b describes the sensitivity of the recovery variable b.
     * @param c describes the after-spike reset vaue of the membrane potential v.
     * @param d describes the after-spike reset of the recovery variable u.
     */
    Neuron(double a,double b,double c,double d);
    /**
     * @brief Destroy the Neuron object
     * 
     */
    virtual ~Neuron();

    /**
    * @brief updates the parameters
    * 
    * Update is 1 simulation step. It updates the paramters of the Neuron using the correct
    * forumla depending on the firing state of the Neuron
    */
    void update();
    /**
     * @brief Set the current paramter
     * 
     * @param current The new current value
     */
    void setCurrent(const double current){_current=current;};
    
    
    /**
     * @brief Computes the noise produced by the neuron
     * 
     * @return (double) The noise produced 
     */
    double noise() const {return this->getW() * (_RNG->normal(0,1));};
    
    /**
     * @brief Descrbies the firing state of the neuron
     * 
     * @return true When v passes the threshold
     * @return false When v is under the threshold
     */
    bool isFiring();

    /**
     * @brief pure virtual method returning the W of the neuron
     * 
     * @return int w of the neuron
     */
    virtual int getW() const = 0;
    /**
     * @brief pure virtual method return the factor of the neuron
     * 
     * @return int factor of the neuron
     */
    virtual int factor() const = 0;

    private:
    double _a;
    double _b;
    double _c;
    double _d;
    double _v;
    double _u;
    double _current;
};


#endif //NEURON_HPP