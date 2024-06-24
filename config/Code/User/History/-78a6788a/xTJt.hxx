#pragma once
#include "CoM3DOFDetailed.hxx"
#include <vector>

void CoM3DOF(std::vector<double> x, std::vector<double> g, std::pair<double, double> DL, double rho, std::vector<double> tu, std::vector<double> mu) {

    CoM3DOFDetailed_initialize();

    CoM3DOFDetailed_U.x[0] = 111;

    CoM3DOFDetailed_step();

    CoM3DOFDetailed_terminate();

    return;
}