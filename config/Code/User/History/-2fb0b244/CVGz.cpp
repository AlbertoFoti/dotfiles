#include "CoM3DOF.hxx"

CoM3DOFresult CoM3DOF(std::array<double, 6> x, std::array<double, 3> g, std::array<double, 2> DL, double rho, double mu) {
    CoM3DOFresult res {};

    // Initialize and prepare input
    CoM3DOFDetailed_initialize();

    CoM3DOFDetailed_U.x[0] = x[0];
    CoM3DOFDetailed_U.x[1] = x[1];
    CoM3DOFDetailed_U.x[2] = x[2];
    CoM3DOFDetailed_U.x[3] = x[3];
    CoM3DOFDetailed_U.x[4] = x[4];
    CoM3DOFDetailed_U.x[5] = x[5];

    CoM3DOFDetailed_U.grav[0] = g[0];
    CoM3DOFDetailed_U.grav[1] = g[1];
    CoM3DOFDetailed_U.grav[2] = g[2];

    CoM3DOFDetailed_U.DL[0] = DL.at(0);
    CoM3DOFDetailed_U.DL[1] = DL.at(1);
    CoM3DOFDetailed_U.rho = rho;

    // Step
    CoM3DOFDetailed_step();

    // Collect results and terminate
    res.xDotOut = {
        CoM3DOFDetailed_Y.x_dot[0],
        CoM3DOFDetailed_Y.x_dot[1],
        CoM3DOFDetailed_Y.x_dot[2],
        CoM3DOFDetailed_Y.x_dot[3],
        CoM3DOFDetailed_Y.x_dot[4],
        CoM3DOFDetailed_Y.x_dot[5],
    };

    res.rho = CoM3DOFDetailed_Y.inVarOut[0];
    res.FD = CoM3DOFDetailed_Y.inVarOut[1];
    res.FL = CoM3DOFDetailed_Y.inVarOut[2];

    CoM3DOFDetailed_terminate();
    return res;
}