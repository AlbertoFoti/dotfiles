#include "LSsolve.hxx"
#include "LinSysSolve.hxx"

std::vector<double> LSsolve(MatrixT m_in, std::vector<double> v_in, uint32_t size1, uint32_t size2) {
    LinSysSolve_initialize();

    LinSysSolve_step();

    LinSysSolve_terminate();
}