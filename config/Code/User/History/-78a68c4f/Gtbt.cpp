#include "CoM3DOF.hxx"

void CoM3DOF(std::array<double, 6> x, std::array<double, 3> g, std::array<double, 2> DL, double rho, double mu) {

    CoM3DOFDetailed_initialize();

    CoM3DOFDetailed_U.x[0] = 111;

    CoM3DOFDetailed_step();

    CoM3DOFDetailed_terminate();

    return;
}