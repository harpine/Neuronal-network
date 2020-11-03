#include <iostream>
#include "random.hpp"
#include <algorithm>

Random::Random(unsigned long int s) : seed(s) {
    if (seed == 0) {
        std::random_device rd;
        seed = rd();
    }
    rng.seed(seed);
}

double Random::exponential(const double rate) {
	std::exponential_distribution<> exp(rate);
	return exp(rng);
}

double Random::normal(double mean, double sd) {
	std::normal_distribution<> norm(mean, sd);
	return norm(rng);
}

int Random::poisson(double mean) {
	std::poisson_distribution<> pois(mean);
	return pois(rng);
}

double Random::uniform_double(double lower, double upper) {
	std::uniform_real_distribution<> unif(lower, upper);
	return unif(rng);
}

int Random::uniform_int (int lower, int upper) {
	std::uniform_int_distribution<> unif(lower, upper);
	return unif(rng);
}

bool Random::bernouilli(double p) {
    std::bernoulli_distribution bernou(p);
    return bernou(rng);
}