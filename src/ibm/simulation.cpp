#include <stdexcept>
#include <random>
#include <cassert>
#include "simulation.hpp"
#include "individual.hpp"


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

// produce new offspring
void Simulation::produce_offspring(unsigned int const n_offspring_required)
{
    // remove existing newborn offspring
    offspring.clear();

    // parent sampler sampling parental indices
    // between 0 and nparents - 1
    std::uniform_int_distribution <unsigned int> parent_sampler(0, 
            population.size() - 1);

    unsigned int father, mother;

    double resources_needed;

    // make new offspring
    for (unsigned int offspring_idx = 0; 
            offspring_idx < n_offspring_required;
            ++offspring_idx)
    {
        // have a number of attempts to sample offspring
        for (int attempt_idx = 0; 
                attempt_idx = params.max_offspring_attempts; 
                ++attempt_idx)
        {
            mother = parent_sampler(rng_r);
            father = parent_sampler(rng_r);

            if (population[mother].resources <= 0.0)
            {
                continue;
            }

            Individual kid(
                    population[mother], 
                    population[father],
                    rng_r);

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

// determine offspring phenotype to be either z1 (false)
// or z2 (true)
bool Simulation::determine_offspring_phenotype(Individual const &mom
                ,Individual const &kid
                ,bool envt)
{
    double maternal_signal_prob_t1 = mom.s[envt][0][0] + mom.s[envt][0][1];

    double maternal_signal_prob_t2 = mom.s[envt][1][0] + mom.s[envt][1][1];

    bool signal_t1 = uniform(rng) < maternal_signal_prob_t1;
    bool signal_t2 = uniform(rng) < maternal_signal_prob_t2;

    int options[2][2] = {{0,1},{2,3}};

    double prob_z1 = q[options[signal_t1][signal_t2]]
}


