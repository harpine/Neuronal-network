#include <gtest/gtest.h>
#include "../src/random.hpp"
#include "../src/simulation.hpp"
#include "../src/constants.hpp"

TEST(testing,thetest){
    EXPECT_EQ(0,0);
}

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


int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}