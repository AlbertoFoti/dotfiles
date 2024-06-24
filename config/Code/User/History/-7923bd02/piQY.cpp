#include "CoM2DOF.hxx"

CoM2DOFresult CoM2DOF(std::array<double, 3> x, double ug, std::array<double, 2> DL, double rho) {
    CoM2DOFresult res {};

    // Initialize and prepare input
    CoM3DOFDetailed_initialize();
    //CoM3DOFDetailed_U.x[0] = 111;

    // Step
    CoM3DOFDetailed_step();

    // Collect results and terminate
    res.xDotOut = {
        COM2DOFDetailed_Y.x_dot[0],
        COM2DOFDetailed_Y.x_dot[1],
        COM2DOFDetailed_Y.x_dot[2]
    };

    res.rho = CoM2DOFDetailed_Y.inVarOut[0];
    res.FD = CoM2DOFDetailed_Y.inVarOut[1];
    res.FL = CoM2DOFDetailed_Y.inVarOut[2];

    CoM3DOFDetailed_terminate();
    return res;
}