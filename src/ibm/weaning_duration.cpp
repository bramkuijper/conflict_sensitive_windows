#include "simulation.hpp"
#include "individual.hpp"
#include "parameters.hpp"

int main(int argc, char **argv)
{
    // allocate a parameter object containing default parameters
    Parameters params;

    params.base_name = argv[1];

    // initialize the simulation
    Simulation sim(params);

    // run the simulation
    sim.run();

    return 0;
}
