#ifndef _INDIVIDUAL_HPP_
#define _INDIVIDUAL_HPP_

// the individual class

class Individual {
    
    public:
        // diploid sensitivity locus for the two timesteps
        double s[2][2] = {{0.0,0.0},{0.0,0.0}};

        // response locus in offspring
        // s[0] * s[1] -- handled by q[3]
        // (1-s[0]) * s[1] -- handled by q[2]
        // s[0] * (1-s[1]) -- handled by q[1]
        // (1-s[0]) * (1-s[1]) -- handled by q[0]
        double q[4] = {0.0,0.0,0.0,0.0};
        constexpr Individual() {};
};

#endif
