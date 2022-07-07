#include "simulation.hpp"
#include "individual.hpp"
#include "parameters.hpp"

int main(int argc, char **argv)
{
    // allocate a parameter object containing default parameters
    Parameters params;

    params.base_name = argv[1];
    params.envt_change[0] = std::stod(argv[2]);
    params.envt_change[1] = std::stod(argv[3]);

    // initialize the simulation
    Simulation sim(params);

    // run the simulation
    sim.run();

    return 0;
}
