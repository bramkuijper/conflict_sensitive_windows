#ifndef _SIMULATION_LIB_HPP
#define _SIMULATION_LIB_HPP

#include <array>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include "individual.hpp"
#include "parameters.hpp"


class Simulation
{
    private:
        // a random devide that is responsible for setting seeds 
        // for the random number generator
        std::random_device rd;
        
        // store the random seed
        unsigned int seed;

        // the random number generator
        std::mt19937 rng_r;

        // struct with parameters - these are initialized in the constructor
        // and after that kept constant (hence const)
        Parameters const params; 

        // the output file to which data and parameters will be written
        std::ofstream output_file;

        std::uniform_real_distribution<double> uniform;

        long unsigned generation = 0;

        // stats
        double mean_number_offspring = 0;
        double mean_number_survivors = 0;
        double mean_proportion_z2 = 0;

    public:
        std::vector<Individual> population;
        std::vector<Individual> offspring;

        // current environment and that of the next time step
        // this is important if we assume that the environment changes
        // right after the first timestep of providing info to offspring 
        bool environment = 0;
        bool environment_future = 0;
        Simulation(Parameters const &params);
        
        void run();
        
        void mortality();
        
        void change_envt();

        // calculate the cost to a mother of producing an offspring
        double calculate_offspring_cost(Individual const &mom
                ,Individual const &kid
                ,bool envt);

        void produce_offspring(unsigned int const n_offspring_required);

        // write headers to the data file
        void write_data_headers();
        void write_data();
};

#endif
