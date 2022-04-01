#ifndef _SIMULATION_LIB_HPP
#define _SIMULATION_LIB_HPP

#include <array>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <ctime>
#include "individual.hpp"

// container of all the parameters used in this simulation
struct Parameters
{
    // initial value for the offspring sensitivity loci
    std::array <double, 4> init_q = {0.5,0.5,0.5,0.5};

    // initial value for the maternal signaling loci
    std::array <double, 2> init_s = {0.5,0.5};

    // population size used in the simulation
    unsigned population_size = 5000;
    // number of generations the simulation is supposed to run
    unsigned long number_generations = 50000;

    // rate of environmental change
    std::array <double, 2> envt_change = {0.5,0.5}; 

    std::string base_name = "sim_sensitive_window";

    int seed = ::time(NULL);
};

class Simulation
{
    private:
        // struct with parameters - these are initialized in the constructor
        // and after that kept constant (hence const)
        Parameters const params; 
        std::ofstream output_file;

        std::random_device rd;
        std::mt19937 rng_r;

    public:
        std::vector<Individual> population;
        std::vector<Individual> offspring;
        Simulation(Parameters const &params);
        void run();
        void mortality();
        void produce_offspring(unsigned int const n_offspring_required);

};

#endif
