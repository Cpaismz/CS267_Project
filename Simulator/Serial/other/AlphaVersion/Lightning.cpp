#include "Lightning.h"

#include <cmath>
#include <cstdlib>

int Lightning::Lambda_Simple_Test(int period) {
    // TODO: fix because RNG is bad
    int selected_week = std::rand() % 12 + 1;
    return selected_week;
}

int Lightning::Lambda_NH(int period, bool verbose) {
    double fire_rate = 0.5;
    double alfa_fact = 0.1;
    double poisson_mean = (fire_rate / 2.0) * (2.0 + alfa_fact * ((period * period) - (period - 1) * (period - 1) - 2.0));
    double probsNoFire = std::cmath.exp(-1 * poisson_mean); // TODO: why do you round?
    
    // https://stackoverflow.com/a/9879024  
    int random_num = ((double) (std::rand()) ) / (std::RAND_MAX);

    return random_num > probsNoFire;
}


int Lightning::Lambda_H(int period, bool verbose) {
    double poisson_mean = 0.5;
    double probsNoFire = std::cmath.exp(-1 * poisson_mean); // TODO: why do you round?
    
    // https://stackoverflow.com/a/9879024  
    int random_num = ((double) (std::rand()) ) / (std::RAND_MAX);

    return random_num > probsNoFire;
}