#include "LSsolve.hxx"
#include "LinSysSolve.hxx"

std::vector<double> LSsolve(MatrixT m_in, std::vector<double> v_in, uint32_t size1, uint32_t size2) {
    LinSysSolve_initialize();

    for(unsigned int i=0; i<m_in.size().at(0); i++) {
        for(unsigned int j=0; j<m_in.size().at(1); j++) {
            LinSysSolve_U.m[i*6+j] = m_in.get(i, j);
        }
    }
    for(unsigned int i=0; i<v_in.size(); i++) {
        LinSysSolve_U.v[i] = v_in.at(i);
    }
    LinSysSolve_U.size1 = size1;
    LinSysSolve_U.size2 = size2;

    LinSysSolve_step();

    std::vector<double> res;
    for(unsigned int i=0; i<m_in.size().at(1); i++) {
        res.push_back(LinSysSolve_Y.sol[i]);
    }

    LinSysSolve_terminate();
}