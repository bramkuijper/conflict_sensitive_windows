#include <gtest/gtest.h>
#include "simulation.hpp"
#include "individual.hpp"

TEST(SimulationTest, PopSizeInitializationEqualToParams) {
    Parameters params;
    Simulation sim(params);

    EXPECT_EQ(sim.population.size(), params.population_size);
}

TEST(SimulationTest, OffspringProduced) 
{
    Parameters params;
    Simulation sim(params);
    
    EXPECT_TRUE(sim.offspring.size() > 0);
    
    sim.produce_offspring(1);

    EXPECT_TRUE(sim.offspring.size() > 0);
}
