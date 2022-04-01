#include <array>
#include <iostream>
#include <random>
#include "individual.hpp"

Individual::Individual(
        std::array <double, 4> const &qarg, 
        std::array < double, 2> const &sarg) :
    q{{qarg[0],qarg[1],qarg[2],qarg[3]}}
    ,s{{{sarg[0],sarg[0]},{sarg[1],sarg[1]}}}
{
} // end Individual::Individual()

Individual::Individual(
        Individual const &mom
        ,Individual const &dad
        ,std::mt19937 &rng)
{
    std::bernoulli_distribution segregator(0.5);

    // segrate paternal and maternal alleles
    for (size_t q_type_idx = 0; q_type_idx < 4; ++q_type_idx)
    {
        q[q_type_idx][0] = mom.q[q_type_idx][segregator(rng)];
        q[q_type_idx][1] = dad.q[q_type_idx][segregator(rng)];
    }

    for (size_t signal_time_idx = 0; signal_time_idx < 2; ++signal_time_idx)
    {
        for (size_t signal_envt_idx = 0; signal_envt_idx < 2; ++signal_envt_idx)
        {
        }
    }

}// end Individual::Individual()
