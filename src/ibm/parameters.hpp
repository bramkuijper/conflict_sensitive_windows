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

    double maternal_resources = 3.0;

    // maximum number of attempts per offspring
    // to sample parents with enough resources
    unsigned max_offspring_attempts = 5;

    // population size used in the simulation
    unsigned population_size = 5000;

    // number of time steps the simulation is supposed to run
    unsigned long number_timesteps = 50000;

    // rate of environmental change 
    // first element from envt 1 to 2
    // second element from envt 2 to 1
    std::array <double, 2> envt_change = {0.5,0.5}; 

    // costs of producing z1, z2 to the mother
    std::array <double, 2> offspring_costs = {1.0,2.0};

    std::array <double, 2> survival_when_maladapted = {0.1,0.1};

    std::string base_name = "sim_sensitive_window";

    // mutation rates for q,s 
    double mu_q = 0.01;
    double mu_s = 0.01;

    // standard deviation of the mutational distribution
    // mutations are sampled from a normal distribution with
    // mean 0 and variance sdmu
    double sdmu = 0.05;

};

#endif
