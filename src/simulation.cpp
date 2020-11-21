#include "simulation.hpp"
#include "constants.hpp"

Simulation::Simulation(std::string outfile)
    : _dt(_DELTA_T_), _time(_END_TIME_), _net( new Network(_MOD_, _NB_, _PERC_, _INT_, _LAMB_, _DEL_)), _outfile(outfile) {}

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
            TCLAP::ValueArg<std::string> rep("r", "repartition", _REP_TEXT_, false, _REP_, "double");
            cmd.add(rep);
            TCLAP::ValueArg<double> lambda("l", "lambda", _LAMBDA_, false, _LAMB_, "double");
            cmd.add(lambda);
            TCLAP::ValueArg<double> inten("i", "intensity", _INTENSITY_, false, _INT_, "double");
            cmd.add(inten);
            TCLAP::ValueArg<std::string> ofile("o", "outptut", _OFILE_TEXT_, false, _OUTFILE_, "string");
            cmd.add(ofile);
            TCLAP::ValueArg<char> model("m", "model", _MODEL_TEXT_, false, _MOD_, "char");
            cmd.add(model);
            TCLAP::ValueArg<double> delta("d", "delta", _D_TEXT_, false, _DEL_, "double");
            cmd.add(delta);
            TCLAP::SwitchArg option("c", "options", _OPTION_TEXT_, false);
            cmd.add(option);
            cmd.parse(argc, argv);

            if(time.getValue() <= 0) throw std::domain_error("The running time of the simulation must be positive");
            if(number.getValue() <= 0) throw std::domain_error("The number of neuron must be positive");
            if(lambda.getValue() <= 0) throw std::domain_error("The mean connection between neurons must be positive and not exceed the number of neuron");
            char mod(std::tolower(model.getValue())); //in case upper case letter
            if (!(mod=='o' or mod=='b' or mod=='c')) throw std::domain_error("The model chosen is not o, c or b");
            _time = time.getValue();
            _options = option.getValue();
            std::string outname = ofile.getValue();
            double tmp = (number.getValue() - 1);
            if ((rep.getValue()).empty()) {
                _net = new Network(mod, number.getValue(), perc.getValue(), inten.getValue(), std::min(lambda.getValue(), tmp), delta.getValue());
            } else {
                double FS(0), IB(0), RZ(0), LTS(0);
                readLine(rep.getValue(), FS, IB, RZ, LTS);
                _net = new Network(mod, number.getValue(), FS, IB, RZ, LTS, inten.getValue(), std::min(lambda.getValue(), tmp), delta.getValue());
            }
            if(outname.length()) _outfile.open(outname);
            
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    } 

Simulation::~Simulation() 
{
    delete _net;
}

int Simulation::run() {
    time_t ex_time = time(NULL);
    struct tm * ptm;
    double running_time(0);
    int index = 1;
    while (running_time < _time) {
        running_time += 2*_dt;
        _net->update();
        print(index);
        index += 1;
    } 
    if(_options) {
        testParamPrint();
        testSamplePrint();
    }
    ex_time = time(NULL);
    ptm = gmtime(&ex_time);
    _outfile.close();
    return ptm->tm_sec;
}

void Simulation::print(int index) {
    std::ostream *outstr = &std::cout;
    if (_outfile.is_open()) outstr = &_outfile;

    std::vector<bool> matrix = _net->getCurrentstatus();
    *outstr << index << " "; 
    for(auto neuron : matrix) {
        *outstr << neuron << " ";
    }
    *outstr << "\n";
}

void Simulation::testParamPrint() {
    std::ostream *outstr = &std::cout; //pas nécessaire ?
    std::ofstream param;
    param.open(_PARAMETERS_);
    if (param.is_open()) outstr = &param;

    std::vector<Neuron*> netw(_net->getNet());
    std::vector<std::map<Neuron*, double>> con(_net->getCon());
    std::vector<double> attributs;
    int inhib(0);
    *outstr << "\t a\t b\t c\t d\t Inhibitory\t degree\t valence\n"; //déterminer si valence utile
    for(size_t i(0); i<netw.size(); ++i) {
        attributs = netw[i]->getAttributs();
        *outstr << i+1 << "\t ";
        for (size_t j(0); j<attributs.size(); ++j) *outstr << attributs[j] << "\t";
        if (netw[i]->getW() == 2) inhib = 1;
        *outstr << inhib << "\t" << con[i].size() << "\t valence\n";
    }
    param.close();
}


void Simulation::testSamplePrint() {
    std::ostream *outstr = &std::cout; //pas nécessaire ?
    std::ofstream samples;
    samples.open(_SAMPLES_);
    if (samples.is_open()) outstr = &samples;

    std::vector<Neuron*> netw(_net->getNet());
    *outstr << "FS.v\t FS.u\t FS.I\t RS.v\t RS.u\t RS.I\n";
    std::vector<double> attributs;
    int index(0);
    for (double running_time(0); running_time < _time; running_time += 2*_dt) {
        attributs = netw[netw.size()-1]->getVariables(); //inhibitory
        for (size_t j(0); j<attributs.size(); ++j) *outstr << index <<attributs[j] << "\t" ;
        attributs = netw[0]->getVariables(); //excitatory
        for (size_t j(0); j<attributs.size(); ++j) *outstr << attributs[j] << "\t" ;
        ++index;
    }
   samples.close();
}

void Simulation::readLine(std::string& line,  double& fs, double& ib, double& rz, double& lts) 
{
    std::string value, key;
    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
    std::stringstream ss(line);
    while (std::getline(ss, value, ':')) 
    {
        if (key.empty()) continue;
        std::getline(ss, value, ',');
        if (key == "FS") fs = stod(value);
        if (key == "IB") ib = stod(value);
        if (key == "RZ") rz = stod(value);
        if (key == "LTS") lts = stod(value); //faire aussi CH ???
        //undifined are RS (excitateurs)
    }
    if (std::abs(fs+ib+rz+lts > 1)) {
        throw std::logic_error("The sum of all proportions is greater than 1");
    }
}