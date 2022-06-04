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
        std::uniform_real_distribution<double> uniform;

    public:
        std::vector<Individual> population;
        std::vector<Individual> offspring;
        bool environment = 0;
        Simulation(Parameters const &params);
        
        void run();
        
        void mortality();
        
        void change_envt();

        // calculate the cost to a mother of producing an offspring
        double calculate_offspring_cost(Individual const &mom
                ,Individual const &kid
                ,bool envt);

        void produce_offspring(unsigned int const n_offspring_required);

};

#endif
