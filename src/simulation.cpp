#include "simulation.hpp"
#include "constants.hpp"

Simulation::Simulation(std::string outfile)
    : _dt(_DELTA_T_), _time(_END_TIME_), _net( new Network(_NB_, _PERC_, _INT_, _LAMB_)), _outfile(outfile) {}

Simulation::Simulation(int argc, char** argv)
    : _dt(_DELTA_T_)
    {
        try {
            std::string path_outfile(_PATH_OUTFILE_);
            std::string outfile(path_outfile + _OUTFILE_);
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
            TCLAP::ValueArg<std::string> ofile("o", "outptut", _OFILE_TEXT_, false, outfile, "string");
            cmd.add(ofile);
            cmd.parse(argc, argv);

            if(time.getValue() <= 0) throw std::domain_error("The running time of the simulation must be positive");
            if(number.getValue() <= 0) throw std::domain_error("The number of neuron must be positive");
            if(lambda.getValue() <= 0) throw std::domain_error("The mean connection between neurons must be positive and not exceed the number of neuron");
            _time = time.getValue();
            std::string outname = ofile.getValue();
            double tmp = (number.getValue() - 1);
            _net = new Network(number.getValue(), perc.getValue(), inten.getValue(), std::min(lambda.getValue(), tmp));
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
    time_t ex_time = time(NULL);
    struct tm * ptm;
    double running_time(0);
    while (running_time < _time) {
        running_time += 2*dt;
        _net->update();
        print();
    } 
    ex_time = time(NULL);
    ptm = gmtime(&ex_time);
    _outfile.close();
    return ptm->tm_sec;
}

void Simulation::print() {
    std::ostream *outstr = &std::cout;
    if (_outfile.is_open()) outstr = &_outfile;

    std::vector<bool> matrix = _net->getCurrentstatus();
    for(auto neuron : matrix) {
        *outstr << neuron << " ";
    }
    *outstr << "\n";
}
