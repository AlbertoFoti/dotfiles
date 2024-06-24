#pragma once
#include "CoM3DOFDetailed.hxx"
#include <array>
#include <vector>

struct CoM3DOFresult {
    std::array<double, 6> xOut {};
};

void CoM3DOF(std::array<double, 6> x, std::array<double, 3> g, std::array<double, 2> DL, double rho, double mu);