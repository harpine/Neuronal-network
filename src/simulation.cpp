#include "simulation.hpp"
#include "constants.hpp"

Simulation::Simulation(int argc, char** argv)
    : _dt(0.5)
    {
        try {
            TCLAP::CmdLine cmd(_PRGRM_TEXT_);
            TCLAP::ValueArg<int> time("t", "time", _TIME_TEXT_, false, _END_TIME_, "int");            
            cmd.add(time);
            TCLAP::ValueArg<int> number("n", "number", _NEURON_NUMBER_, false, _NB_, "int");
            cmd.add(number);
            TCLAP::ValueArg<double> perc("p", "p_E", _PERCENT_ACTIVE_, false, _PERC_, "double");
            cmd.add(perc);
            TCLAP::ValueArg<double> lambda("l", "lambda", _LAMBDA_, false, _LAMB_, "double");
            cmd.add(lambda);
            TCLAP::ValueArg<double> inten("i", "intensity", _INTENSITY_, false, _INT_, "double");
            cmd.add(inten);
            TCLAP::ValueArg<std::string> ofile("o", "outptut", _OFILE_TEXT_, false, "", "string");
            cmd.add(ofile);
            cmd.parse(argc, argv);

            if(time.getValue() <= 0) throw std::domain_error("The running time of the simulation must be positive");
            if(number.getValue() <= 0) throw std::domain_error("The number of neuron must be positive");
            if(lambda.getValue() <= 0 or lambda.getValue() >= (number.getValue() -1)) throw std::domain_error("The mean connection between neurons must be positive and not exceed the number of neuron");
            _time = time.getValue();
            this->_net = new Network(number.getValue(), perc.getValue(), inten.getValue(), lambda.getValue());

        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    } 

Simulation::~Simulation() 
{
    delete _net;
}

void Simulation::run(double dt, double time) {
    double running_time(0);
    while (running_time <= time) {
        running_time += dt;
        _net->update();
    }
}

