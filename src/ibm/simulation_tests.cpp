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

    EXPECT_FALSE(envt_orig, envt_new);
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

    EXPECT_FALSE(envt_orig, envt_new);
} // end EnvtSame

TEST(SimulationTest, CostCorrect)
{
    Parameters params;

    Individual mom;
    Individual kid;

    Simulation sim(params);

    // envt 1
    bool envt = true;

    double costs = sim.calculate_offspring_cost(mom, kid, envt);

    // costs are equal to
    // f_i * gamma_i + (1.0 - f_i) * beta_i
    // obvz this is going to change once we have a more realistic
    // model of sensitive windows in which resources are gradually
    // passed around from parent to offspring

    
} // end CostCorrect
