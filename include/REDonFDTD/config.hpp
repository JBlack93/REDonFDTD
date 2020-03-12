/** @file config.hpp
 *  @brief Contains the configuration class */
#pragma once

#include <cmath>
#include <array>

namespace REDonFDTD {

//! @brief Class containing the configuration of the run of REDonFDTD
  struct config {
    int sizeX = 51;                                     //!< x-dimension of Mesh
    int sizeY = 50;                                     //!< y-dimension of Mesh
    int sizeZ = 50;                                     //!< z-dimension of Mesh
    int steps = 100;                                    //!< Number of Steps
    long double timeStep = 5e-10;                       //!< Duration of each step
    double ppw = 15.;
    std::array<double,3> position = {25.,25.,25.};
    std::array<double,3> velocity = {0.,0.5,0.};
    std::array<double,3> acceleration = {0.,0.,0.};
  };
}
