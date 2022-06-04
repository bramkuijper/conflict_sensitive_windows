#include "individual.hpp"
#include "parameters.hpp"

int main(int argc, char **argv)
{
    // allocate a parameter object containing default parameters
    Parameters params;

    // initialize the simulation
    Simulation sim(params);

    // run the simulation
    sim.run();

    return 0;
}
