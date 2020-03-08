/** @file config.hpp
 *  @brief Contains the configuration class */
#pragma once

#include <cmath>

namespace REDonFDTD {

//! @brief Class containing the configuration of the run of REDonFDTD
  class config {
  public:
    config() = default;
    ~config() = default;
    const int sizeX = 51;                                     //!< x-dimension of Mesh
    const int sizeY = 50;                                     //!< y-dimension of Mesh
    const int sizeZ = 50;                                     //!< z-dimension of Mesh
    const int steps = 100;                                    //!< Number of Steps
    const long double timeStep = 5*pow(10,-10);               //!< Duration of each step
    const long double maxTime = steps*timeStep;               //!< duration of simulation
    const long double cdtds = 1.0 / sqrt(3.0);                //!< Courant number
  };
}
