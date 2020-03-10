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
    const int sizeX = 101;                                     //!< x-dimension of Mesh
    const int sizeY = 100;                                     //!< y-dimension of Mesh
    const int sizeZ = 100;                                     //!< z-dimension of Mesh
    const int steps = 100;                                    //!< Number of Steps
    const long double timeStep = 5e-10;                       //!< Duration of each step
    const long double maxTime = steps*timeStep;               //!< Duration of simulation
    const long double cdtds = 1.0 / sqrt(3.0);                //!< Courant number
    const double c = 2.99792458e8;                            //!< Speed of light
    const double epsilon_0 = 8.85418782e-12;                  //!< Permittivity of free space
    const double Mu_0 = M_PI*4e-7;                            //!< Magnetic Permeability
    const double dS = c*timeStep;                             //!< Grid Spacing
  };
}
