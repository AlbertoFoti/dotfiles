#include "CoM3DOF.hxx"

CoM3DOFresult CoM3DOF(std::array<double, 6> x, std::array<double, 3> g, std::array<double, 2> DL, double rho, double mu) {
    CoM3DOFresult res {};

    // Initialize and prepare input
    CoM3DOFDetailed_initialize();
    CoM3DOFDetailed_U.x[0] = 111;

    // Step
    CoM3DOFDetailed_step();

    // Collect results and terminate
    res.xOut = CoM3DOFDetailed_Y.x_dot;
  
    CoM3DOFDetailed_terminate();
    return;
}