#pragma once
#include "COM2DOFDetailed.hxx"
#include <array>
#include <vector>

typedef struct CoM2DOFresult_t {
    std::array<double, 3> xDotOut {};
    double rho {};
    double FD {};
    double FL {};
} CoM2DOFresult;

CoM2DOFresult CoM2DOF(std::array<double, 3> x, double ug, std::array<double, 2> DL, double rho);