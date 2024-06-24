#pragma once
#include "CoM3DOFDetailed.hxx"
#include <array>
#include <vector>

typedef struct CoM3DOFresult_t {
    std::array<double, 6> xOut {};
} CoM3DOFresult;

CoM3DOFresult CoM3DOF(std::array<double, 6> x, std::array<double, 3> g, std::array<double, 2> DL, double rho, double mu);