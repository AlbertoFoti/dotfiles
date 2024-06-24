#pragma once
#include "CoM3DOFDetailed.hxx"
#include <vector>

void CoM3DOF(std::array<double, 6> x, std::array<double, 3> g, std::array<double, 2> DL, double rho, std::vector<double> tu, std::vector<double> mu);