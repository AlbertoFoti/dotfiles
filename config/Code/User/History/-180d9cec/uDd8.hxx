#pragma once
#include <array>
#include "type_defines.hxx"

class GE_Grav01_class
{
public:
  std::array<double, 3> GE_Grav_Exec(std::array<double, 6> xCoMNav);
};

