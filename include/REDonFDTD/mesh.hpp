/** @file mesh.hpp
 *  @brief Contains the Mesh class */
#pragma once

#include <cmath>
#include <vector>
#include "REDonFDTD/memAllocation.hpp"

namespace REDonFDTD {

//! @brief Mesh is the 4D space-time grid which contains both E and H fields.
  class Mesh {
  public:
    Mesh(int x, int y, int z);
    ~Mesh() = default;

//! @brief Update the E-Field in the space-time Mesh
    void updateE();
//! @brief Update the H-Field in the space-time Mesh
    void updateH();

    std::vector<double> hx, chxh, chxe;              //!< H_x field. Plus coefficients needed in its Update equation
    std::vector<double> hy, chyh, chye;              //!< H_y field. Plus coefficients needed in its Update equation
    std::vector<double> hz, chzh, chze;              //!< H_z field. Plus coefficients needed in its Update equation
    std::vector<double> ex, cexe, cexh;              //!< E_x field. Plus coefficients needed in its Update equation
    std::vector<double> ey, ceye, ceyh;              //!< E_y field. Plus coefficients needed in its Update equation
    std::vector<double>  ez, ceze, cezh;              //!< E_z field. Plus coefficients needed in its Update equation
    int sizeX, sizeY, sizeZ;               //!<  Dimensions of the Mesh
    long double time, timeStep, maxTime;   //!< Define advance in time.
    double cdtds;                          //!< Courant number (Maximal distance which can be traveled in a timestep)

    const double c = 2.99792458e8;
    const double epsilon_0 = 8.85418782e-12;
    const double Mu_0 = M_PI*4e-7;

  };
}
