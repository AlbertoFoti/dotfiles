#pragma once
#include "CoM3DOFDetailed.hxx"
#include <array>
#include <vector>

typedef struct CoM2DOFresult_t {
    std::array<double, 3> xDotOut {};
    double rho {};
    double FD {};
    double FL {};
} CoM2DOFresult;

CoM2DOFresult CoM2DOF(std::array<double, 3> x, std::array<double, 3> g, std::array<double, 2> DL, double rho, double mu);