#include "LSsolve.hxx"
#include "LinSysSolve.hxx"

std::vector<double> LSsolve(MatrixT m_in, std::vector<double> v_in, uint32_t size1, uint32_t size2) {
    LinSysSolve_initialize();

    for(unsigned int i=0; i<m_in.size().at(0); i++) {
        for(unsigned int i=0; i<m_in.size().at(1); i++) {
            LinSysSolve_U.v[i] = v_in.at(i);
        }
    }
    for(unsigned int i=0; i<v_in.size(); i++) {
        LinSysSolve_U.v[i] = v_in.at(i);
    }
    LinSysSolve_U.size1 = size1;
    LinSysSolve_U.size2 = size2;

    LinSysSolve_step();

    LinSysSolve_terminate();
}