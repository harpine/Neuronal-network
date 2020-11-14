#include <gtest/gtest.h>
#include "../src/random.hpp"
#include "../src/simulation.hpp"
#include "../src/constants.hpp"
#include "../src/excitatoryNeuron.hpp"
#include "../src/inhibitoryNeuron.hpp"

Random* _RNG = new Random(23948710923);

TEST(Random, distributions) {
    double mean = 0;
    double input_mean(1.35), input_sd(2.8);
    std::vector<double> res;
    res.resize(10000);
    double delta = input_sd*sqrt(3.0);
    double lower = input_mean-delta, upper = input_mean+delta;
    _RNG->uniform_double(res, lower, upper);
    for (auto I : res) {
        EXPECT_GE(I, lower);
        EXPECT_LT(I, upper);
        mean += I*1e-4;
    }
    EXPECT_NEAR(input_mean, mean, 3e-2*input_sd);
    _RNG->normal(res, input_mean, input_sd);
    mean = 0;
    for (auto I : res) mean += I*1e-4;
    EXPECT_NEAR(input_mean, mean, 2e-2*input_sd);
    _RNG->poisson(res, input_mean);
    mean = 0;
    for (auto I : res) mean += I*1e-4;
    EXPECT_NEAR(input_mean, mean, 2e-2*input_mean);
}

TEST(Network, connections) {
    size_t test_size(6);
    Network net(int(test_size), _PERC_, _INT_, _LAMB_);
    std::vector<Neuron*> netw(net.getNet());
    std::vector<std::map<Neuron*, double>> con(net.getCon());

    //test création Network
    EXPECT_FALSE(netw.empty());
    EXPECT_FALSE(con.empty());

    //test bon nombre neurones crées
    EXPECT_EQ(test_size, netw.size());
    EXPECT_EQ(con.size(), netw.size());

    //test association map/neurone
    int problems(0);
    for (size_t i(0); i<netw.size(); ++i) {
        for (auto pair : con[i]) {
            if(pair.first == netw[i]) ++problems;
        }   
    }
    EXPECT_EQ(problems, 0);

    //test pas nullptr
    int sumNull(0);
    for (size_t i(0); i<netw.size(); ++i) {
        if (netw[i]==nullptr) ++sumNull;
    }
    EXPECT_EQ(sumNull, 0);
    sumNull = 0;
    for (size_t i(0); i<con.size(); ++i) {
        for (auto& pair : con[i]) {
            if (pair.first == nullptr) ++sumNull;
        }
    }
    EXPECT_EQ(sumNull, 0);
    
}

TEST(Simulation, output) {
    Simulation sim(_OUTFILE_);
    int result = sim.run(_DELTA_T_);
    EXPECT_LE(result, 60);

    std::string print = sim.read_file(_OUTFILE_);
    size_t nb_line(0);
    size_t nb_column(0);
    bool value = false;
    for (size_t i(1); i<=print.size(); ++i) {
        size_t j(i-1);
        if(print[i] == '\n') nb_line +=1;
        if((print[i] == ' ') and (print[j] == '\n')) nb_column +=1;
        if((print[i] != ' ') or (print[i] != '\n') or 
           (print[i] != '1') or (print[i] != '0')) value = true;
    }
    EXPECT_EQ(nb_line, _END_TIME_);
    EXPECT_EQ(nb_column, _NB_);
    EXPECT_FALSE(value);
}

TEST(Neuron, attributs){
    double r=1.0;
    ExcitatoryNeuron* excitatory= new ExcitatoryNeuron(r);
    InhibitoryNeuron* inhibitory= new InhibitoryNeuron(r);
    std::vector<double> excit_attributs={0.1*(1-0.8*r),0.2*(1+0.25*r),-65,2};
    std::vector<double> inhib_attributs={0.02,0.2,-65*(1-(1/13))*r*r,8*(1-(3/4))*r*r};
    for(size_t i(0);i<excit_attributs.size();++i){
        EXPECT_EQ(excitatory->getAttributs()[i],excit_attributs[i]);
        EXPECT_EQ(inhibitory->getAttributs()[i],inhib_attributs[i]);
    }
}
TEST(Neuron, update){
    double r=1.0;
    ExcitatoryNeuron* excitatory= new ExcitatoryNeuron(r);
    InhibitoryNeuron* inhibitory= new InhibitoryNeuron(r);
    std::vector<double> excit_variablesInitial=excitatory->getVariables();
    std::vector<double> inhib_varaiblesInitial=inhibitory->getVariables();
    excitatory->update();
    inhibitory->update();
    for(size_t i(0);i<excit_variablesInitial.size();++i){
        EXPECT_NE(excit_variablesInitial[i],excitatory->getVariables()[i]);
        EXPECT_NE(inhib_varaiblesInitial[i],inhibitory->getVariables()[i]);
    }
}

int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}