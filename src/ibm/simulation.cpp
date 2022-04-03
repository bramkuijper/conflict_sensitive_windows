#include <stdexcept>
#include <random>
#include <cassert>
#include "simulation.hpp"
#include "individual.hpp"

Simulation::Simulation(Parameters const &params) :
    params(params)
    ,population(params.population_size) // initialize all individuals
    ,output_file(params.base_name.c_str())
    ,rng_r(rd())
{
    if (params.population_size < 1)
    {
        throw std::range_error("Population size 0");
    }
    
    rng_r.seed(params.seed);

}// end Simulation::Simulation

// running the actual simulation over time
void Simulation::run()
{
    int n_offspring;
    for (unsigned long generation = 0; 
            generation < params.number_generations;
            ++generation)
    {
        mortality();

        n_offspring = params.population_size - population.size();
        assert(n_offspring >= 0);

        produce_offspring(n_offspring);
    } // end for unsigned generation
}// end run

// produce new offspring
void Simulation::produce_offspring(unsigned int const n_offspring_required)
{
    // TODO we need to think about resources
    // remove existing offspring
    offspring.clear();

    // parent sampler sampling parental indices
    // between 0 and nparents - 1
    std::uniform_int_distribution <unsigned int> parent_sampler(0, 
            population.size() - 1);

    unsigned int father, mother;

    // make new offspring
    for (unsigned int offspring_idx = 0; 
            offspring_idx < n_offspring_required;
            ++offspring_idx)
    {
        mother = parent_sampler(rng_r);
        father = parent_sampler(rng_r);

        Individual kid(
                population[mother], 
                population[father],
                rng_r);

        // add kid to stack of offspring
        offspring.push_back(kid);
    }
} // void Simulation::produce_offspring

// parental mortality function
void Simulation::mortality()
{

}

