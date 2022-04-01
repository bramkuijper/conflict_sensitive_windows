#ifndef _INDIVIDUAL_HPP_
#define _INDIVIDUAL_HPP_

#include <array>
#include <random>
// the individual class

class Individual {
    
    public:
        // diploid sensitivity locus for the two timesteps
        std::array < std::array <double, 2>, 2> s = {{{0.0,0.0},{0.0,0.0}}};

        // response locus in offspring
        // s[0] * s[1] -- handled by q[3]
        // (1-s[0]) * s[1] -- handled by q[2]
        // s[0] * (1-s[1]) -- handled by q[1]
        // (1-s[0]) * (1-s[1]) -- handled by q[0]
        std::array <std::array <double, 2>, 4> q = {{{0.0,0.0}
                                                        ,{0.0,0.0}
                                                        ,{0.0,0.0}
                                                        ,{0.0,0.0}}};

        constexpr Individual() {}; // default constructor

        // argument-based constructo
        Individual(std::array <double, 4> const &q, 
                std::array <double, 2> const &s);

        Individual(
                Individual const &mom
                ,Individual const &dad
                ,std::mt19937 &rng
                );
};

#endif
