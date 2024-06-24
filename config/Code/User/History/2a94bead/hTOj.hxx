#include "MatrixInverse.hxx"

void inverseMatrix(std::vector<std::vector<double>> m_in) {
    MatrixInverse_initialize();

    MatrixInverse_step();

    MatrixInverse_terminate();
}