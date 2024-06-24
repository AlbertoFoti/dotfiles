#include "Matrix.hxx"
#include "MatrixInverse/MatInv.hxx"

MatrixT::MatrixT() {
    this->data = std::vector<std::vector<double>>();
}

MatrixT::MatrixT(std::vector<std::vector<double>> data) {
    this->data = data;
}

MatrixT::MatrixT(std::vector<std::array<double, 4>> data) {
    for(unsigned int i=0; i<data.size(); i++) {
    std::vector<double> item;
    for(unsigned int j=0; j<4; j++) {
        item.push_back(data.at(i).at(j));
    }
    this->data.push_back(item);
    }
}

MatrixT::MatrixT(std::size_t size1, std::size_t size2) {
    for(unsigned int i=0; i<size1; i++) {
        std::vector<double> item;
        for(unsigned int j=0; j<size2; j++) {
            item.push_back(0.00);
        }
        this->data.push_back(item);
    }
}

MatrixT MatrixT::eye(uint32_t size) {
    MatrixT res;

    for(unsigned int i=0; i<size; i++) {
    std::vector<double> item;
    for(unsigned int j=0; j<size; j++) {
        if(i == j) {
        item.push_back(1.00);
        } else {
        item.push_back(0.00);
        }
    }
    res.data.push_back(item);
    }

    return res;
}

MatrixT MatrixT::diag(std::vector<double> v) {
    MatrixT res;
    size_t size = v.size();

    for(unsigned int i=0; i<size; i++) {
        std::vector<double> item;
        for(unsigned int j=0; j<size; j++) {
            if(i == j) {
                item.push_back(v.at(i));
            } else {
                item.push_back(0.00);
            }
        }
        res.data.push_back(item);
    }

    return res;
}

MatrixT MatrixT::transpose(MatrixT m) {
    MatrixT res;

    for(unsigned int i=1; i<m.size().at(0); i++) {
        for(unsigned int j=0; j<m.size().at(1); j++) {
            
        }
    }

    return res;
}

MatrixT MatrixT::slice(MatrixT& m_in, 
    std::pair<uint32_t, uint32_t> range1,
    std::pair<uint32_t, uint32_t> range2
) {
    MatrixT res;

    for(unsigned int i=range1.first; i<range1.second; i++) {
    std::vector<double> item;
    for(unsigned int j=range2.first; j<range2.second; j++) {
        item.push_back(m_in.data.at(i).at(j));
    }
    res.data.push_back(item);
    }

    return res;
}

MatrixT MatrixT::sliceRows(MatrixT& m_in, 
    std::pair<uint32_t, uint32_t> range
) {
    MatrixT res;

    for(unsigned int i=range.first; i<range.second; i++) {
        res.data.push_back(m_in.at(i));
    }

    return res;
}

MatrixT MatrixT::fillBackCol(MatrixT in_mat, std::vector<double> end_col) {
    MatrixT res;
    res.data = in_mat.data;

    for(unsigned int i=0; i<in_mat.size().at(0); i++) {
        res.data.at(i).at(res.data.at(i).size()) = end_col.at(i);
    }

    return res;
}

void MatrixT::fillCol(size_t ix_col, std::vector<double> col) {
    for(unsigned int i=0; i<this->size().at(0); i++) {
        this->data.at(i).at(ix_col) = col.at(i);
    }
}

MatrixT MatrixT::inverse(MatrixT& m_in) {
    return MatrixT(inverseMatrix(m_in.data, m_in.data.size()));
}

MatrixT MatrixT::scalarMul(double alpha, MatrixT m_in) {
    MatrixT res;
    res.data = m_in.data;

    for(unsigned int i=0; i<m_in.size().at(0); i++) {
        for(unsigned int j=0; j<m_in.size().at(1); j++) {
            res.data.at(i).at(j) = alpha + m_in.get(i, j);
        }
    }

    return res;
}

MatrixT MatrixT::matrixSum(MatrixT m1, MatrixT m2) {
    MatrixT res;
    res.data = m1.data;
    
    for(unsigned int i=0; i<m1.size().at(0); i++) {
        for(unsigned int j=0; j<m1.size().at(1); j++) {
            res.data.at(i).at(j) = m1.get(i, j) + m2.get(i, j);
        }
    }

    return res;
}

MatrixT MatrixT::matrixMul(MatrixT m1, MatrixT m2) {
    size_t rows1 = m1.data.size();
    size_t cols1 = m1.data.at(0).size();
    size_t cols2 = m2.data.at(0).size();

    auto res = MatrixT(rows1, cols2);

    if(m1.size().at(0) != m2.size().at(1)) {
        // Todo Handle Error
        return res;
    }

    for(size_t i=0; i<rows1; i++) {
        for(size_t j=0; j<cols2; j++) {
            res.data.at(i).at(j) = 0.0;
            for(size_t k=0; k<cols1; k++) {
                res.data.at(i).at(j) += m1.data.at(i).at(k) * m2.data.at(k).at(j);
            }
        }
    }

    return res;
}

std::vector<double> MatrixT::matrixMul(MatrixT m1, std::vector<double> v) {
    std::vector<double> res;

    if(m1.size().at(1) != v.size()) {
        // Todo Handle Error
        return res;
    }

    for(size_t i=0; i<m1.size().at(0); i++) {
        double elem = 0;
        for(unsigned int j=0; j<v.size(); j++) {
            elem += m1.get(i, j)*v.at(j);
        }   
        res.push_back(elem);
    }

    return res;
}

std::vector<double> MatrixT::at(uint32_t row) {
    return this->data.at(row);
}

std::vector<double> MatrixT::getCol(uint32_t col) {
    std::vector<double> res;

    for(unsigned int i=0; i<this->data.size(); i++) {
    res.push_back(this->data.at(i).at(col));
    }

    return res;
}

std::vector<uint32_t> MatrixT::size() {
    std::vector<uint32_t> res;

    res.push_back(this->data.size());
    res.push_back(this->data.at(0).size());

    return res;
}

std::vector<double> MatrixT::backRow() {
    return this->data.back();
}

double MatrixT::get(uint32_t row, uint32_t col) {
    return this->data.at(row).at(col);
}

void MatrixT::clear() {
    this->data.clear();
}