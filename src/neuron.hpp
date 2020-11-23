#ifndef NEURON_HPP
#define NEURON_HPP
#include <vector>
#include <string>
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
     * @param type string indicating the type of the Neuron 
     */
    Neuron(std::string type);
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
     * @brief Getter for the _a,_b,_c,_d attributes
     * 
     * @return std::vector<double> {_a,_b,_c,_d}
     */
    std::vector<double> getAttributs();
    /**
     * @brief Getter for the _v,_u variables
     * 
     * @return std::vector<double> {_v,_u}
     */
    std::vector<double> getVariables();
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
    /**
     * @brief 
     * 
     */
    std::string getType() const; 


    protected:
    double _a;
    /**
     * @brief describes the sensitivity of the recovery variable v.
     * 
     */
    double _b;
    /**
     * @brief describes the after-spike reset value of the membrane potential v.
     * 
     */
    double _c;
    /**
     * @brief describes the after-spike reset of the recovery variable u.
     * 
     */
    double _d;
    double _v;
    double _u;
    double _current;
    std::string _type;
};


#endif //NEURON_HPP