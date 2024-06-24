#include "MatInv.hxx"

void inverseMatrix(std::vector<std::vector<double>> m_in, uint32_t NbrNom) {
    MatrixInverse_initialize();
    uint32_t size = m_in.size();

    for(unsigned int i=0; i<m_in.size(); i++) {
        for(unsigned int j=0; j<m_in.at(0).size(); j++) {
            MatrixInverse_U.u[i*8+j] = m_in.at(i).at(j);
        }
    }

    MatrixInverse_step();

    std::vector<std::vector<double>> res;
    for(unsigned int i=0; i<NbrNom; i++) {
        std::vector<double> item;
        for(unsigned int j=0; j<NbrNom; j++) {
            item.push_back(MatrixInverse_Y.y[i*8+j]);
        }
        res.push_back(item);
    }

    MatrixInverse_terminate();
}