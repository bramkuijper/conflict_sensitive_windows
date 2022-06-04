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
        // struct with parameters - these are initialized in the constructor
        // and after that kept constant (hence const)
        Parameters const params; 
        std::ofstream output_file;

        std::random_device rd;
        std::mt19937 rng_r;
        std::uniform_real_distribution<double> uniform;

        long unsigned generation = 0;

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

        // write headers to the data file
        void write_data_headers();
        void write_data();
};

#endif
