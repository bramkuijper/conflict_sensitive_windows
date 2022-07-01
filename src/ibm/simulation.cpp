#include <stdexcept>
#include <random>
#include <cassert>
#include "simulation.hpp"
#include "individual.hpp"
#include "parameters.hpp"


// see also the corresponding header file simulation.hpp

// initialize a single individual-based simulation
Simulation::Simulation(Parameters const &params) :
    rd{}
    ,seed{rd()}
    ,rng_r{seed}
    ,params(params) // set the parameters
    ,output_file(params.base_name.c_str()) // start the output files
    ,uniform(0.0,1.0)
    ,population(  // initialize all individuals in the vector population
            params.population_size // this is the number of individuals
            ,Individual(params.maternal_resources // give each individual resources
                        ,params.init_q // initial values for the q vector
                        ,params.init_s) // initial values for the s vector
            ) 
{
    // if population size 0, throw an error
    if (params.population_size < 1)
    {
        throw std::range_error("Population size 0");
    }
}// end Simulation::Simulation

// running the actual simulation over 
// params.number_timesteps of generations
void Simulation::run()
{
    // auxiliary variable to determine #offspring
    // that need to be produced in this time step
    int n_offspring;

    write_data_headers();

    for (time_step = 0; 
            time_step < params.number_timesteps;
            ++time_step)
    {
        mortality();

        n_offspring = params.population_size - population.size();
        assert(n_offspring >= 0);

        produce_offspring(n_offspring);

        change_envt();

        if (time_step % params.output_interval == 0)
        {
            write_data();
        }

    } // end for generation
}// end run

void Simulation::write_data()
{
    double meanq[4] = {0.0,0.0,0.0};
    double varq[4] = {0.0,0.0,0.0};

    double means[2][2] = {{0.0,0.0},{0.0,0.0}};
    double vars[2][2] = {{0.0,0.0},{0.0,0.0}};

    double q,s;

    for (int individual_idx = 0; 
            individual_idx < population.size(); ++individual_idx)
    {
        // output the mean values of q
        for (int q_type_idx = 0; q_type_idx < 4; ++q_type_idx)
        {
            q = population[individual_idx].q[q_type_idx][0]
                + population[individual_idx].q[q_type_idx][1];

            meanq[q_type_idx] += q;

            // store sum of squares
            varq[q_type_idx] += q * q;
        }

        // headers for the different values of the maternal signal loci s_ij
        for (int signal_envt_idx = 0; signal_envt_idx < 2; signal_envt_idx++)
        {
            for (int signal_time_idx = 0; signal_time_idx < 2; signal_time_idx++)
            {
                s = 0.5 * (population[individual_idx].s[signal_envt_idx][signal_time_idx][0] 
                        + population[individual_idx].s[signal_envt_idx][signal_time_idx][1]);

                means[signal_envt_idx][signal_time_idx] += s;

                // store sum of squares
                vars[signal_envt_idx][signal_time_idx] += s * s;
            }
        }
    } // end for (int individual_idx

    output_file << time_step << ";"
        << environment << ";"
        << mean_number_offspring << ";"
        << mean_number_survivors << ";"
        << mean_proportion_z2 << ";";
    
    // output the mean values of q
    for (int q_type_idx = 0; q_type_idx < 4; ++q_type_idx)
    {
        // mean value of q
        meanq[q_type_idx] /= population.size();

        // var = SS[x] / N - E[x]^2
        varq[q_type_idx] = varq[q_type_idx] / population.size() 
            - meanq[q_type_idx] * meanq[q_type_idx];

        output_file << meanq[q_type_idx] << ";";
        output_file << varq[q_type_idx] << ";";
    }

    for (int signal_envt_idx = 0; signal_envt_idx < 2; signal_envt_idx++)
    {
        for (int signal_time_idx = 0; signal_time_idx < 2; signal_time_idx++)
        {
            means[signal_envt_idx][signal_time_idx] /= population.size();

            // var = SS[x] / N - E[x]^2
            vars[signal_envt_idx][signal_time_idx] = 
                vars[signal_envt_idx][signal_time_idx] / population.size() 
                    - means[signal_envt_idx][signal_time_idx] *
                        means[signal_envt_idx][signal_time_idx];

            output_file << means[signal_envt_idx][signal_time_idx] << ";";
            output_file << vars[signal_envt_idx][signal_time_idx] << ";";
        }
    }

    output_file << std::endl;
} // end write_data()

// write the headers of the data file
void Simulation::write_data_headers()
{
    output_file << "generation;envt;mean_number_offspring;mean_number_adult_survivors;mean_proportion_z2;";

    // headers for the different values of the offspring response loci, q_i
    for (int q_type_idx = 0; q_type_idx < 4; ++q_type_idx)
    {
        output_file << "meanq" << q_type_idx << ";"
                    << "varq" << q_type_idx << ";";
    }

    // headers for the different values of the maternal signal loci s_ij
    for (int signal_envt_idx = 0; signal_envt_idx < 2; signal_envt_idx++)
    {
        for (int signal_time_idx = 0; signal_time_idx < 2; signal_time_idx++)
        {
            output_file << "means_e" << signal_envt_idx 
                                << "t" << signal_time_idx << ";"
                        << "vars_e" << signal_envt_idx 
                                << "t" << signal_time_idx << ";";
        }
    }

    // end with newline, after which the data will be written to the file
    output_file << std::endl;
} // end write_data_headers()

// write parameters to the output file
void Simulation::write_parameters()
{
    output_file << std::endl
        << std::endl
        << "seed;" << seed << std::endl
        << "envt_change_1;" << params.envt_change[0] << std::endl
        << "envt_change_2;" << params.envt_change[1] << std::endl
        << "cost_z1;" << params.offspring_costs[0] << std::endl
        << "cost_z2;" << params.offspring_costs[1] << std::endl
        << "survival_maladapted_1;" << params.survival_when_maladapted[0] << std::endl
        << "survival_maladapted_2;" << params.survival_when_maladapted[1] << std::endl;
}

// produce a new offspring
void Simulation::produce_offspring(unsigned int const n_offspring_required)
{
    // population extinct...
    if (population.size() < 2)
    {
        write_parameters();
        exit(1);
    }

    // remove any newborn offspring from the previous generation
    offspring.clear();

    // reset some stats
    mean_proportion_z2 = 0.0;
    int total_number_offspring = 0;

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
    unsigned int father_idx;

    // aux variable that stores the result
    // of the amount of resources needed for each offspring
    double resources_needed;

    // go through all parents 
    // and have them produce offspring
    // based on their resources
    for (int mother_idx = 0; mother_idx < population.size(); ++mother_idx)
    {
        // give mother her standard resources
        // this assumes that resources do not carry over between years
        population[mother_idx].resources = params.maternal_resources;

        while (population[mother_idx].resources > 0.0)
        {
            // sample any other individual that is the father
            // i.e., as in a hermaphroditic system. This is just easier
            // than modeling separate sexes and as only the mother delivers
            // the resources the outcomes are effectively the same
            father_idx = father_sampler(rng_r);

            // to assess how much resources an offspring needs
            // we first need to produce it
            //
            // hence, produce an offspring
            Individual kid(
                    population[mother_idx],  // kid's mom
                    population[father_idx], // kid's dad
                    environment, // current envt
                    environment_future, // future envt
                    params, // parameters (to determine mutation rates)
                    rng_r // random number generator
                    );

            // calculate amount of resources that we need
            // at the moment we assume these resources are envt independent
            resources_needed = params.offspring_costs[kid.phenotype_z2];

            // mom has more resources than needed, 
            // just produce the offspring
            if (population[mother_idx].resources > resources_needed)
            {
                // update stats
                mean_proportion_z2 += kid.phenotype_z2;
                ++total_number_offspring;

                // subtract needed resources
                population[mother_idx].resources -= resources_needed;
                offspring.push_back(kid);
            }
            else  // too few resources to produce kid
            {
                // however with some luck may still produce offspring
                // with a probability proportional to actual amount of resources 
                // available, relative to resources required. For example, if 
                // required resource is 10 units, but mom only has 8 units available
                // she will produce offspring with probability 0.8
                double fraction_resources = 
                    population[mother_idx].resources / resources_needed;

                if (uniform(rng_r) < fraction_resources)
                {
                    // update stats
                    mean_proportion_z2 += kid.phenotype_z2;
                    ++total_number_offspring;

                    offspring.push_back(kid);
                }

                // regardless of her actually producing 
                // the half-baked offspring
                // this will be her last attempt as she has now
                // ran out of resources
                population[mother_idx].resources = 0.0;
            }
        }// end while resources
    } // end for (int mother_idx = 0

    // update stats
    // so far we have total count of z2 offspring
    // to calculate proportion divide by total # offspring
    mean_proportion_z2 /= total_number_offspring;

    // calculate mean number of offspring
    mean_number_offspring = total_number_offspring / population.size();

} // void Simulation::produce_offspring

// parental mortality function
void Simulation::mortality()
{
    // aux variable denoting a survival probability
    double survival_prob;

    mean_number_survivors = 0;

    if (offspring.size() < 1)
    {
        return;
    }

    // sample from offspring distribution
    std::uniform_int_distribution<> offspring_sampler(0, offspring.size() - 1);

    // go through all parents 
    // and have them produce offspring
    // based on their resources
    for (int individual_idx = 0; 
            individual_idx < population.size(); ++individual_idx)
    {
        survival_prob = 
            // adult experiences the experiment after switching
            population[individual_idx].phenotype_z2 == environment_future ?
                params.survival_when_maladapted[environment_future]
                :
                params.background_mortality;
   
        // to survive uniform random number should fall
        // in the interval 0 - survival_prob
        // if it does not, as per below, individual does not survive
        if (uniform(rng_r) > survival_prob)
        {
            // replace adult by newborn
            population[individual_idx] = offspring[offspring_sampler(rng_r)];
        }
        else
        {
            ++mean_number_survivors;
        }
    }
} // end Simulation::mortality()

// change the global environment
// we always work two steps ahead
// as we need to have knowledge both about the current
// and the future envt when doing the sensitive window thingy
void Simulation::change_envt()
{
    // make the environment
    environment = environment_future;

    if (uniform(rng_r) < params.envt_change[environment_future])
    {
        environment_future = !environment_future;
    }
} // end change_envt()

