#include <gtest/gtest.h>
#include "individual.hpp"

// check whether traits are indeed at 0 when allocating a 
// default individual
TEST(IndividualTest, DefaultIndividualTraitsZero) {
    Individual ind;
    EXPECT_EQ(ind.s[0],0.0);
}
