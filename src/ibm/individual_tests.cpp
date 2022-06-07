#include <gtest/gtest.h>
#include <vector>
#include <random>
#include "individual.hpp"

// check whether traits are indeed at 0 when allocating a 
// default individual
TEST(IndividualTest, DefaultSTraitsZero) {
    Individual ind;
    EXPECT_EQ(ind.s[0][0][0],0.0);
    EXPECT_EQ(ind.s[0][1][0],0.0);
    EXPECT_EQ(ind.s[1][0][1],0.0);
    EXPECT_EQ(ind.s[1][1][1],0.0);
}

TEST(IndividualTest, DefaultQTraitsZero) {
    Individual ind;
    EXPECT_EQ(ind.q[0][0],0.0);
    EXPECT_EQ(ind.q[1][0],0.0);
    EXPECT_EQ(ind.q[2][0],0.0);
    EXPECT_EQ(ind.q[3][0],0.0);
}

TEST(IndividualTest, CopyConstructort) {
    double val = 0.5;
    Individual ind1;
    ind1.s[0][1][0] = val; 

    Individual ind2(ind1);

    EXPECT_EQ(ind1.s[0][1][0],ind2.s[0][1][0]);
    EXPECT_EQ(ind2.s[0][1][0],val);
}

TEST(IndividualTest, AddToVector) {

    std::size_t len = 2;
    std::vector <Individual> a_couple(len);

    EXPECT_EQ(a_couple.size(),2);
}

TEST(IndividualTest, ParentCtorTest) {

    Individual mom;
    Individual dad;

    dad.q[0][0] = 0.5;
    dad.q[0][1] = 0.5;

    std::random_device rd;
    unsigned seed = rd();
    std::mt19937 rng_r{seed};

    Parameters params;

    Individual kid1(mom
            ,dad
            ,0
            ,0
            ,params
            ,rng_r);

    Individual kid2(mom
            ,dad
            ,0
            ,0
            ,params
            ,rng_r);

    EXPECT_TRUE(kid1.q[0][0] + kid1.q[0][1] > 0.0);
    EXPECT_FALSE(kid2.q[0][0] + kid2.q[0][1] > 0.0);
}
