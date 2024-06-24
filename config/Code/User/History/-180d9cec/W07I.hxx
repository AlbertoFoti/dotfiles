#pragma once
#include <array>
#include "type_defines.hxx"

class GEGrav
{
public:
  static std::array<double, 3> GE_Grav_Exec(PlanetGravStr PlanetGrav, std::array<double, 6> xCoMNav);
};

