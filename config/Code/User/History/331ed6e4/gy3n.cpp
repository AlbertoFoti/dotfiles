#include "Utils.hxx"

std::vector<double> linspace(double start_in, double end_in, int num_in)
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

std::vector<double> acos_vectorial(std::vector<double> data) {
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

std::vector<std::vector<double>> zeros(std::size_t size1, std::size_t size2) {
    std::vector<std::vector<double>> res;

    for(unsigned int i=0; i<size1; i++) {
      std::vector<double> item;
      for(unsigned int j=0; j<size2; j++) {
        item.push_back(0.00);
      }
      res.push_back(item);
    }

    return res;
}

void sum(std::vector<double>& vector_a, std::vector<double>& vector_b) {
    for(unsigned int i=0; i<vector_a.size(); i++) {
        vector_a.at(i) += vector_b.at(i);
    }
}

int32_t sign(double num) {
  if (num < 0.00) {
    return -1;
  } else if (num > 0.00) {
    return 1;
  } else {
    return 0;
  }
}

std::vector<double> diff(std::vector<double> vec) {
  std::vector<double> res;

  for(unsigned int i=1; i<vec.size(); i++) {
    res.push_back(vec.at(i) - vec.at(i-1));
  }

  return res;
}

std::vector<double> diff(std::vector<uint32_t> vec) {
  std::vector<double> res;

  for(unsigned int i=1; i<vec.size(); i++) {
    res.push_back(vec.at(i) - vec.at(i-1));
  }

  return res;
}

std::vector<std::vector<double>> randi(RandomGen& rg, double max, uint32_t size1, uint32_t size2) {
  std::vector<std::vector<double>> res;

  for(unsigned int i=0; i<size1; i++) {
    std::vector<double> item;
    for(unsigned int j=0; j<size2; j++) {
      double rand_num = rg.rand_gen();
      if(rand_num > max) {
        rand_num -= max;
      }
      item.push_back(rand_num);
    }
    res.push_back(item);
  }

  return res;
}

std::vector<double> vectorSum(std::vector<double>& v1, std::vector<double>& v2) {
  std::vector<double> res {};

  if(v1.size() != v2.size()) {
    // TODO: Handle Error
    return res;
  }

  for(unsigned int i=0; i<v1.size(); i++) {
    res.push_back(v1.at(i) + v2.at(i));
  }

  return res;
}

std::vector<uint32_t> vectorGreater(std::vector<double> v1, double threshold) {
  std::vector<uint32_t> res;

  for(unsigned int i=0; i<v1.size(); i++) {
    if(v1.at(i) > threshold) {
      res.push_back(1);
    } else {
      res.push_back(0);
    }
  }

  return res;
}

std::array<double, 4> array4Sum(std::array<double, 4> v1, std::array<double, 4> v2) {
  std::array<double, 4> res {};

  for(unsigned int i=0; i<v1.size(); i++) {
    res.at(i) = v1.at(i) + v2.at(i);
  }

  return res;
}

std::vector<double> vectorSlice(std::vector<double>& vec, std::pair<double, double> range) {
  std::vector<double> res {};
  for(unsigned int i=range.first; i<range.second; i++) {
    res.push_back(vec.at(i));
  }

  return res;
}

std::vector<uint32_t> find_vectorial(std::vector<double>& v1, double threshold) {
  std::vector<uint32_t> res;

  for(unsigned int i=0; i<v1.size(); i++) {
    if(v1.at(i) > threshold) {
      res.push_back(1);
    } else {
      res.push_back(0);
    }
  }

  return res;
}

std::vector<uint32_t> find(std::vector<uint32_t> vec) {
  std::vector<uint32_t> res;

  for(unsigned int i=0; i<vec.size(); i++) {
    if(vec.at(i) > 0) {
      res.push_back(i);
    }
  }

  return res;
}

std::vector<uint32_t> find(std::vector<double> vec) {
  std::vector<uint32_t> res;

  for(unsigned int i=0; i<vec.size(); i++) {
    if(vec.at(i) > 0) {
      res.push_back(i);
    }
  }

  return res;
}

