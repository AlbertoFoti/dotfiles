#include "CoM2DOF.hxx"

CoM2DOFresult CoM2DOF(std::array<double, 3> x, double ug, std::array<double, 2> DL, double rho) {
    CoM2DOFresult res {};

    // Initialize and prepare input
    COM2DOFDetailed_initialize();
    //CoM3DOFDetailed_U.x[0] = 111;

    // Step
    COM2DOFDetailed_step();

    // Collect results and terminate
    res.xDotOut = {
        COM2DOFDetailed_Y.dx[0],
        COM2DOFDetailed_Y.dx[1],
        COM2DOFDetailed_Y.dx[2]
    };

    COM2DOFDetailed_terminate();
    return res;
}