#pragma once
#include <vector>
#include <array>
#include <cstdint>

class MatrixT {
public:
    std::vector<std::vector<double>> data;

public:
    MatrixT();

    MatrixT(std::vector<std::vector<double>> data);

    MatrixT(std::vector<std::array<double, 4>> data);

    MatrixT(std::size_t size1, std::size_t size2);

    static MatrixT eye(uint32_t size);

    static MatrixT diag(std::vector<double> v);

    static MatrixT transpose(MatrixT m);

    static MatrixT slice(MatrixT& m_in, 
      std::pair<uint32_t, uint32_t> range1,
      std::pair<uint32_t, uint32_t> range2
    );

    static MatrixT sliceRows(MatrixT& m_in, 
      std::pair<uint32_t, uint32_t> range
    );

    static MatrixT fillBackCol(MatrixT in_mat, std::vector<double> end_col);

    void fillCol(size_t ix_col, std::vector<double> col);

    static MatrixT inverse(MatrixT& m_in);

    static MatrixT scalarMul(double alpha, MatrixT m_in);

    static MatrixT matrixSum(MatrixT m1, MatrixT m2);

    static MatrixT matrixMul(MatrixT m1, MatrixT m2);

    static std::vector<double> matrixMul(MatrixT m1, std::vector<double> v);

    std::vector<double> at(uint32_t row);

    std::vector<double> getCol(uint32_t col);

    std::vector<uint32_t> size();

    std::vector<double> backRow();

    double get(uint32_t row, uint32_t col);

    void clear();
};