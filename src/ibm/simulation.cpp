#include <stdexcept>
#include <random>
#include <cassert>
#include "simulation.hpp"
#include "individual.hpp"
#include "parameters.hpp"


// see also the corresponding header file simulation.hpp

// initialize a single individual-based simulation
Simulation::Simulation(Parameters const &params) :
    params(params) // set the parameters
    ,population(  // initialize all individuals in the vector population
            params.population_size // this is the number of individuals
            ,Individual(params.resources // give each individual resources
                        ,params.init_q // initial values for the q vector
                        ,params.init_s) // initial values for the s vector
            ) 
    ,output_file(params.base_name.c_str()) // start the output files
    ,rng_r(rd()) // start the random number generator
    ,uniform(0.0,0.1)
{
    // if population size 0, throw an error
    if (params.population_size < 1)
    {
        throw std::range_error("Population size 0");
    }

    // set the seed of the random number generator
    // the seed is the identifier of the random number sequence
    // if you give 2 simulations the same seed (and other conditions are
    // also the same) their outcomes will be identical. This is great
    // to repeat simulations when hunting for bugs etc, but otherwise
    // the seeds should differ between different runs.
    rng_r.seed(params.seed);
}// end Simulation::Simulation

// running the actual simulation over 
// params.number_timesteps of generations
void Simulation::run()
{
    // auxiliary variable to determine #offspring
    // that need to be produced in this time step
    int n_offspring;


    for (unsigned long generation = 0; 
            generation < params.number_timesteps;
            ++generation)
    {
        mortality();

        n_offspring = params.population_size - population.size();
        assert(n_offspring >= 0);

        produce_offspring(n_offspring);

        change_envt();

    } // end for unsigned generation
}// end run

void Simulation::write_data()
{
    output_file << generation << ";";

    double meanq[4] = {0.0,0.0,0.0};
    double varq[4] = {0.0,0.0,0.0};

    double means[2][2] = {{0.0,0.0},{0.0,0.0}};
    double vars[2][2] = {{0.0,0.0},{0.0,0.0}};

    for (int individual_idx = 0; individual_idx < population.size(); individual_idx)
    {

    }
    output_file << std::endl;
}


void Simulation::write_data_headers()
{
    output_file << "generation;mean_number_offspring;mean_number_adult_survivors;";

    for (int q_type_idx = 0; q_type_idx < 4; ++q_type_idx)
    {
        output_file << "meanq" << q_type_idx << ";"
    }

    for (int signal_envt_idx = 0; signal_envt_idx < 2; signal_envt_idx++)
    {
        for (int signal_time_idx = 0; signal_time_idx < 2; signal_time_idx++)
        {
            output_file << "means_e" << signal_envt_idx << "t" << signal_time_idx << ";";
        }
    }

    output_file << std::endl;
}


// produce a new offspring
void Simulation::produce_offspring(unsigned int const n_offspring_required)
{
    // remove existing newborn offspring
    offspring.clear();

    // father sampler sampling parental indices
    // between 0 and nparents - 1
    //
    // note we assume hermaphroditism here, as that is easier than 
    // taking into account separate sexes. See Kuijper & Johnstone 2018
    // for more information
    std::uniform_int_distribution <unsigned int> father_sampler(0, 
            population.size() - 1);

    // auxiliary variable to store currently
    // sampled father and mother
    unsigned int father;

    // aux variable that stores the result
    // of the amount of resources needed for each offspring
    double resources_needed;

    // go through all parents 
    // and have them produce offspring
    // based on their resources
    for (int parent_idx = 0; parent_idx < population.size(); ++parent_idx)
    {
        while (population[mother].resources > 0.0)
        {
            father = parent_sampler(rng_r);

            // to assess how much resources an offspring needs
            // we first need to produce it
            //
            // hence, produce an offspring
            Individual kid(
                    population[mother], 
                    population[father],
                    rng_r);

            // calculate amount of resources that we need
            resources_needed = calculate_offspring_cost(
                    population[mother]
                    ,kid
                    ,environment);

            // mom has more resources than needed, 
            // just produce the offspring
            if (population[mother].resources > resources_needed)
            {
                // subtract needed resources
                population[mother].resources -= resources_needed;
                offspring.push_back(kid);

                break;
            }
            else 
            {
                // population[mother].resources 
                double fraction_resources = 
                    population[mother].resources / resources_needed;

                if (uniform(rng_r) < fraction_resources)
                {
                    offspring.push_back(kid);
                    break;
                }

                population[mother].resources = 0.0;
            }
        }// end for
    }
} // void Simulation::produce_offspring

// parental mortality function
void Simulation::mortality()
{

}

// change the global environment
void Simulation::change_envt()
{

} // end change_envt()


