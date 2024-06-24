#pragma once

#include <vector>
#include <cmath>
#include <cstdint>

#ifdef _USE_MATH_DEFINES
double pi = M_PI;
#else
// Define pi yourself (less recommended)
#endif

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in)
{
  std::vector<double> linspaced;

  double start = static_cast<double>(start_in);
  double end = static_cast<double>(end_in);
  double num = static_cast<double>(num_in);

  if (num == 0) { return linspaced; }
  if (num == 1) 
    {
      linspaced.push_back(start);
      return linspaced;
    }

  double delta = (end - start) / (num - 1);

  for(int i=0; i < num-1; ++i)
    {
      linspaced.push_back(start + delta * i);
    }
  linspaced.push_back(end); // I want to ensure that start and end
                            // are exactly the same as the input
  return linspaced;
}

template<typename T>
std::vector<double> acos_vectorial(std::vector<T> data) {
    std::vector<double> res;

    for(unsigned int i=0; i<data.size(); i++) {
        res.push_back(acos(data.at(i)));
    }

    return res;
}

std::vector<double> zeros(std::size_t size) {
    std::vector<double> res;

    for(unsigned int i=0; i<size; i++) {
        res.push_back(0.00);
    }

    return res;
}

void sum(std::vector<double>& vector_a, std::vector<double>& vector_b) {
    for(unsigned int i=0; i<vector_a.size(); i++) {
        vector_a.at(i) += vector_b.at(i);
    }
}

std::vector<double> find_vectorial(std::vector<double> vec, double value) {
    std::vector<double> res;

    for(unsigned int i=0; i<vec.size(); i++) {
        if(vec.at(i) > value) {
            res.push_back(i);    
        }
    }

    return res;
}