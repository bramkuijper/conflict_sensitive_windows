#ifndef _INDIVIDUAL_HPP_
#define _INDIVIDUAL_HPP_

// include array and random from C++'s standard template library
#include <array>
#include <random>
#include "parameters.hpp"


// the individual class

class Individual {
    
    public:

        // whether individual has phenotype z2
        bool phenotype_z2 = 0;

        double resources = 3.0;

        // diploid sensitivity locus for the two timesteps
        // across the two environments
        // we have
        //  - s11 - signal in envt 1 at time t=1
        //  - s12 - signal in envt 1 at time t=2
        //  - s21 - signal in envt 2 at time t=1
        //  - s22 - signal in envt 2 at time t=2
        //
        //  moreover, each signal is diploid
        //  hence we need a 3 dimensional 2x2x2 array
        //  with the first dimension being environment
        //  the second being time step
        //  and the third dimension being which allele
        std::array < std::array < std::array<double, 2>, 2>, 2 > s = 
        {{
             {{
                 {{0,0}}
                 ,{{0,0}}
              }},
             {{
                 {{0,0}}
                 ,{{0,0}}
              }}
         }};
        // notice extra braces around each extra level
        // https://stackoverflow.com/questions/11734861/when-can-outer-braces-be-omitted-in-an-initializer-list 
            
        // response locus in offspring
        // s[0] * s[1] -- handled by q[3]
        // (1-s[0]) * s[1] -- handled by q[2]
        // s[0] * (1-s[1]) -- handled by q[1]
        // (1-s[0]) * (1-s[1]) -- handled by q[0]
        std::array <std::array <double, 2>, 4> q = 
        {{
             {{0,0}},
             {{0,0}},
             {{0,0}},
             {{0,0}}
        }};

        constexpr Individual() {}; // default constructor

        // argument-based constructor
        Individual(
                double resources
                ,std::array <double, 4 > const &q 
                ,std::array < std::array <double, 2> ,2 > const &s);

        Individual(
                Individual const &mom
                ,Individual const &dad
                ,bool const envt_t1 // environment during time t1
                ,bool const envt_t2 // environment during time t2
                ,Parameters const &params
                ,std::mt19937 &rng
                );
};

#endif
