#include <gtest/gtest.h>
#include "simulation.hpp"
#include "individual.hpp"
#include "parameters.hpp"

TEST(SimulationTest, PopSizeInitializationEqualToParams) {
    Parameters params;
    Simulation sim(params);

    EXPECT_EQ(sim.population.size(), params.population_size);
}

TEST(SimulationTest, OffspringProduced) 
{
    Parameters params;
    Simulation sim(params);
    
    EXPECT_TRUE(sim.offspring.size() == 0);
    
    sim.produce_offspring(1);

    EXPECT_TRUE(sim.offspring.size() > 0);
}

TEST(SimulationTest, EnvtChanged)
{
    Parameters params;

    // change should always happen
    params.envt_change[0] = 1.0;
    params.envt_change[1] = 1.0;

    Simulation sim(params);

    bool envt_orig = sim.environment;
    sim.change_envt();

    bool envt_new = !sim.environment;

    EXPECT_FALSE(envt_orig == envt_new);
}

TEST(SimulationTest, EnvtSame)
{
    Parameters params;

    // change should never happen
    params.envt_change[0] = 0.0;
    params.envt_change[1] = 0.0;

    Simulation sim(params);

    bool envt_orig = sim.environment;
    sim.change_envt();
    
    bool envt_new = !sim.environment;

    EXPECT_FALSE(envt_orig == envt_new);
} // end EnvtSame

