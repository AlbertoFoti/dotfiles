#include "MatrixInverse.hxx"

void inverseMatrix(std::vector<std::vector<double>> m_in) {
    MatrixInverse_initialize();


    for(unsigned int i=0; i<m_in.size(); i++) {
        for(unsigned int j=0; j<m_in.at(0).size(); j++) {
            MatrixInverse_U[i*8+j] = m_in.at(i).at(j);
        }
    }

    MatrixInverse_step();

    MatrixInverse_terminate();
}