#pragma once
#include <random>
#include <vector>

class RandomGen {
public:
    std::mt19937 rand_gen;
    std::vector<std::vector<double>> seedV;
    std::vector<std::vector<double>> seedVemcd;
    std::normal_distribution<double> dis;
};