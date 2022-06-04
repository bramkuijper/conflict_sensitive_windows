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

Individual::Individual(
        Individual const &mom
        ,Individual const &dad
        ,std::mt19937 &rng)
{
    std::bernoulli_distribution diploid_allele_sampler(0.5);

    // segrate paternal and maternal alleles
    for (size_t q_type_idx = 0; q_type_idx < 4; ++q_type_idx)
    {
        q[q_type_idx][0] = mom.q[q_type_idx][diploid_allele_sampler(rng)];
        q[q_type_idx][1] = dad.q[q_type_idx][diploid_allele_sampler(rng)];
    }

    for (size_t signal_envt_idx = 0; signal_envt_idx < 2; ++signal_envt_idx)
    {
        for (size_t signal_time_idx = 0; signal_time_idx < 2; ++signal_time_idx)
        {
            s[signal_envt_idx][signal_time_idx][0] = 
                mom.s[signal_envt_idx][signal_time_idx][diploid_allele_sampler(rng)];

            s[signal_envt_idx][signal_time_idx][1] = 
                dad.s[signal_envt_idx][signal_time_idx][diploid_allele_sampler(rng)];
        }
    }

}// end Individual::Individual()
