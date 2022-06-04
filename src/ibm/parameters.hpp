#include <array>
#include <string>
#include <ctime>

#ifndef _PARAMETERS_HPP_
#define _PARAMETERS_HPP_

// container of all the parameters used in this simulation
struct Parameters
{
    // initial value for the offspring sensitivity loci
    std::array <double, 4> init_q = {{0.5,0.5,0.5,0.5}};

    // initial value for the maternal signaling loci
    // first index is envt second index is time
    std::array < std::array <double, 2>, 2> init_s = {{
        {{0.5,0.5}}
        ,{{0.5,0.5}}
    }};

    double resources = 3.0;

    // maximum number of attempts per offspring
    // to sample parents with enough resources
    unsigned max_offspring_attempts = 5;

    // population size used in the simulation
    unsigned population_size = 5000;

    // number of time steps the simulation is supposed to run
    unsigned long number_timesteps = 50000;

    // rate of environmental change
    std::array <double, 2> envt_change = {0.5,0.5}; 

    // costs of producing z1, z2
    std::array <double, 2> costs = {1.0,2.0};

    std::string base_name = "sim_sensitive_window";

    // the random seed
    int seed = ::time(NULL);

    // mutation rates for q,s 
    double mu_q = 0.01;
    double mu_s = 0.01;

    // standard deviation of the mutational distribution
    // mutations are sampled from a normal distribution with
    // mean 0 and variance sdmu
    double sdmu = 0.05;

};

#endif
