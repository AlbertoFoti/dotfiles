#pragma once
#include <cstdint>
#include "Matrix.hxx"
#include <vector>

std::vector<double> LSsolve(MatrixT m_in, std::vector<double> v_in, uint32_t size1, uint32_t size2);