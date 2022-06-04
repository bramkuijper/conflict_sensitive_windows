#include <array>
#include <iostream>
#include <random>
#include "individual.hpp"

// functions corresponding to the individual class


// constructor function to initialize an individual
// based on default values for the signal response vector q
// and 
Individual::Individual(
        double resources,
        std::array <double, 4> const &qarg, 
        std::array < std::array <double, 2> ,2 > const &sarg
        ) :
    resources{resources}
    ,q{{
        {{qarg[0],qarg[0]}}, // initialize the two alleles of q0
        {{qarg[1],qarg[1]}}, // initialize the two alleles of q1
        {{qarg[2],qarg[2]}},  // initialize the two allels of q2
        {{qarg[3],qarg[3]}}// initialze the two alleles of q3
    }}
    ,s{{ // initialize s with first dimension envt, second dimension time, third dimension which of the two alleles (diploid)
        {{
             {{sarg[0][0],sarg[0][0]}},
             {{sarg[0][1],sarg[0][1]}}
        }},
        {{
             {{sarg[1][0],sarg[1][0]}},
             {{sarg[1][1],sarg[1][1]}}
        }}
    }}
{
} // end Individual::Individual()


// constructor that produces an individual 
// from two parents
Individual::Individual(
        Individual const &mom 
        ,Individual const &dad
        ,bool const envt_t1
        ,bool const envt_t2
        ,Parameters params // a parameter object which contains all the mutation rates
        ,std::mt19937 &rng // as we need to sample parental alleles, we need a random number generator
)
{
    // make an allele sampling function
    std::bernoulli_distribution diploid_allele_sampler{0.5};
    std::uniform_real_distribution uniform{0,1.0};
    std::normal_distribution normal{0,params.sdmu};

    // sample paternal and maternal alleles
    // for each of the sensitivity loci
    for (size_t q_type_idx = 0; q_type_idx < 4; ++q_type_idx)
    {
        // get allele from mother
        q[q_type_idx][0] = mom.q[q_type_idx][diploid_allele_sampler(rng)];

        // see if a mutation applies
        if (uniform(rng) < mu_q)
        {
            // note the clamp() function which ensures
            // values are between 0 - 1.0
           q[q_type_idx][0] = clamp(q[q_type_idx][0] + normal(rng), 0.0, 1.0);
        }

        // get allele from father
        q[q_type_idx][1] = dad.q[q_type_idx][diploid_allele_sampler(rng)];
        
        // see if a mutation applies
        if (uniform(rng) < mu_q)
        {
           q[q_type_idx][1] = clamp(q[q_type_idx][1] + normal(rng), 0.0, 1.0);
        }
    }

    // sample paternal and maternal alleles
    // for each of the signal loci
    for (size_t signal_envt_idx = 0; signal_envt_idx < 2; ++signal_envt_idx)
    {
        for (size_t signal_time_idx = 0; signal_time_idx < 2; ++signal_time_idx)
        {
            s[signal_envt_idx][signal_time_idx][0] = 
                mom.s[signal_envt_idx][signal_time_idx][diploid_allele_sampler(rng)];
        
            // see if a mutation applies
            if (uniform(rng) < mu_s)
            {
               s[signal_envt_idx][signal_time_idx][0] = clamp(s[signal_envt_idx][signal_time_idx][0] + 
                       normal(rng), 0.0, 1.0);
            }

            s[signal_envt_idx][signal_time_idx][1] = 
                dad.s[signal_envt_idx][signal_time_idx][diploid_allele_sampler(rng)];
            
            // see if a mutation applies
            if (uniform(rng) < mu_s)
            {
               s[signal_envt_idx][signal_time_idx][1] = clamp(s[signal_envt_idx][signal_time_idx][1] + 
                       normal(rng), 0.0, 1.0);
            }
        }
    }

    // express the mom's signal during time=t1
    // note that the first index of mom.s reflects the environment
    // the second signal the time step (in this case 0 because it is the first time step)
    // the third the allele (diploidy)
    double maternal_signal_prob_t1 = 0.5 * (mom.s[envt_t1][0][0] + mom.s[envt_t1][0][1]);

    // express the mom's signal during time=t2
    // notice change in 2nd index
    double maternal_signal_prob_t2 = 0.5 * (mom.s[envt_t2][1][0] + mom.s[envt_t2][1][1]);

    // express q loci
    double q_expressed[4] = {
        0.5 * (q[0][0] + q[0][1]),
        0.5 * (q[1][0] + q[1][1]),
        0.5 * (q[2][0] + q[2][1]),
        0.5 * (q[3][0] + q[3][1])};


    q[3] * maternal_signal_prob_t1 * maternal_signal_prob_t2
        + q[2] * (1.0 - 

}// end Individual::Individual()
