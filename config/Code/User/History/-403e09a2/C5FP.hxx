#pragma once

#include <vector>
#include <cmath>

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

template<typename T>
std::vector<double> zeros(uint32_t size) {
    std::vector<double> res;

    for(unsigned int i=0; i<size; i++) {
        res.push_back(0.00);
    }

    return res;
}