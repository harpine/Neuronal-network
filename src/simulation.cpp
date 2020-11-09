#include "simulation.hpp"
#include "constants.hpp"

Simulation::Simulation()
    : _dt(_DELTA_T_), _time(_END_TIME_), _outfile(_OFILE_TEXT_) {}

Simulation::Simulation(int argc, char** argv)
    : _dt(_DELTA_T_)
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
            std::string outname = ofile.getValue();
            this->_net = new Network(number.getValue(), perc.getValue(), inten.getValue(), lambda.getValue());
            if(outname.length()) _outfile.open(outname);
            
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    } 

Simulation::~Simulation() 
{
    delete _net;
}

int Simulation::run(double dt) {
    int ex_time = 0;
    double running_time(0);
    while (running_time <= this->_time) {
        running_time += dt;
        _net->update();
    } 
    ex_time = clock();
    return ex_time;
}

void Simulation::print() {
    std::ostream *outstr = &std::cout;
    if (_outfile.is_open()) outstr = &_outfile;

    std::vector<bool> matrix = _net->getCurrentstatus();
    for (size_t i(0); i<_time; ++i) {
        for(auto neuron : matrix) {
            *outstr << neuron << " ";
        }
        *outstr << "\n" << std::endl;
    }
}
