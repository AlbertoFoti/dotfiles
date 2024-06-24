#pragma once

#include <vector>
#include <cmath>
#include <array>
#include <random>
#include <cstdint>
#include "MatrixInverse/MatInv.hxx"

#define _USE_MATH_DEFINES
#ifdef _USE_MATH_DEFINES
    double pi = M_PI;
#else
#endif

#define DEG2RAD pi/180
#define RAD2DEG 180/pi

std::vector<double> linspace(double start_in, double end_in, int num_in);

std::vector<double> acos_vectorial(std::vector<double> data);

std::vector<double> zeros(std::size_t size);

std::vector<std::vector<double>> zeros(std::size_t size1, std::size_t size2);

void sum(std::vector<double>& vector_a, std::vector<double>& vector_b);

std::vector<uint32_t> find_vectorial_double(std::vector<double>& vec, double value);

std::vector<uint32_t> find_vectorial_uint(std::vector<uint32_t>& vec, uint32_t value);

int32_t sign(double num);

// Function to calculate adjacent difference
std::vector<double> diff(std::vector<double> vec);

std::vector<uint32_t> diff(std::vector<uint32_t> vec);

std::vector<uint32_t> matrixSize(std::vector<std::vector<uint32_t>> input);

std::vector<std::vector<double>> randi(RandomGen& rg, double max, uint32_t size1, uint32_t size2);

std::vector<double> vectorSum(std::vector<double> v1, std::vector<double> v2);

std::vector<double> vectorSlice(std::vector<double> vec, std::pair<double, double> range);

class MatrixT {
public:
    std::vector<std::vector<double>> data;

public:
    MatrixT();

    MatrixT(std::vector<std::vector<double>> data);

    MatrixT(std::vector<std::array<double, 4>> data);

    static MatrixT eye(uint32_t size);

    static MatrixT slice(MatrixT& m_in, 
      std::pair<uint32_t, uint32_t> range1,
      std::pair<uint32_t, uint32_t> range2
    );

    static MatrixT inverse(MatrixT& m_in);

    std::vector<double> at(uint32_t row);

    std::vector<double> getCol(uint32_t col);

    void clear();
};
