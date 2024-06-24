#pragma once

#include <vector>
#include <cmath>
#include <array>
#include <random>
#include <cstdint>
#include "Random.hxx"

std::vector<double> linspace(double start_in, double end_in, int num_in);

std::vector<double> acos_vectorial(std::vector<double> data);

std::vector<double> zeros(std::size_t size);

std::vector<std::vector<double>> zeros(std::size_t size1, std::size_t size2);

void sum(std::vector<double>& vector_a, std::vector<double>& vector_b);

int32_t sign(double num);

// Function to calculate adjacent difference
std::vector<double> diff(std::vector<double> vec);

std::vector<uint32_t> diff(std::vector<uint32_t> vec);

std::vector<std::vector<double>> randi(RandomGen& rg, double max, uint32_t size1, uint32_t size2);

std::vector<double> vectorSum(std::vector<double>& v1, std::vector<double>& v2);
std::vector<uint32_t> vectorGreater(std::vector<double>& v1, std::vector<double>& v2);
std::array<double, 4> array4Sum(std::array<double, 4> v1, std::array<double, 4> v2);

std::vector<double> vectorSlice(std::vector<double>& vec, std::pair<double, double> range);

std::vector<uint32_t> find_vectorial(std::vector<double>& v1, double threshold);

std::vector<uint32_t> find(std::vector<uint32_t>& vec);
std::vector<uint32_t> find(std::vector<double>& vec);
