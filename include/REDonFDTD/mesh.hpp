/** @file mesh.hpp
 *  @brief Contains the Mesh class */
#pragma once

#include <cmath>
#include <vector>

const int x = 51;
const int y = 50;
const int z = 50;

namespace REDonFDTD {

//! @brief Mesh is the 4D space-time grid which contains both E and H fields.
  class Mesh {
  public:
    Mesh();
    ~Mesh() = default;

//! @brief Update the E-Field in the space-time Mesh
    void updateE();
//! @brief Update the H-Field in the space-time Mesh
    void updateH();

    const int sizeX=x;
    const int sizeY=y;
    const int sizeZ=z;               //!<  Dimensions of the Mesh

    std::vector<double> hx   = std::vector<double>(sizeX*(sizeY-1)*(sizeZ-1));   //!< H_x field
    std::vector<double> chxh = std::vector<double>(sizeX*(sizeY-1)*(sizeZ-1));   //!< Hx H coefficient
    std::vector<double> chxe = std::vector<double>(sizeX*(sizeY-1)*(sizeZ-1));   //!< Hx E coefficient

    std::vector<double> hy   = std::vector<double>(sizeZ*(sizeY-1)*(sizeX-1));   //!< H_y field
    std::vector<double> chyh = std::vector<double>(sizeZ*(sizeY-1)*(sizeX-1));   //!< Hy H coefficient
    std::vector<double> chye = std::vector<double>(sizeZ*(sizeY-1)*(sizeX-1));   //!< Hy E coefficient

    std::vector<double> hz   = std::vector<double>(sizeY*(sizeZ-1)*(sizeX-1));   //!< H_z field
    std::vector<double> chzh = std::vector<double>(sizeY*(sizeZ-1)*(sizeX-1));   //!< Hz H coefficient
    std::vector<double> chze = std::vector<double>(sizeY*(sizeZ-1)*(sizeX-1));   //!< Hz E coefficient

    std::vector<double> ex   = std::vector<double>(sizeZ*(sizeY)*(sizeX-1));     //!< E_x field
    std::vector<double> cexh = std::vector<double>(sizeZ*(sizeY)*(sizeX-1));     //!< Ex H coefficient
    std::vector<double> cexe = std::vector<double>(sizeZ*(sizeY)*(sizeX-1));     //!< Ex E coefficient

    std::vector<double> ey   = std::vector<double>(sizeZ*(sizeY-1)*(sizeX));     //!< E_y field
    std::vector<double> ceyh = std::vector<double>(sizeZ*(sizeY-1)*(sizeX));     //!< Ey H coefficient
    std::vector<double> ceye = std::vector<double>(sizeZ*(sizeY-1)*(sizeX));     //!< Ey E coefficient

    std::vector<double> ez   = std::vector<double>(sizeY*(sizeZ-1)*(sizeX));     //!< E_z field
    std::vector<double> cezh = std::vector<double>(sizeY*(sizeZ-1)*(sizeX));     //!< Ez H coefficient
    std::vector<double> ceze = std::vector<double>(sizeY*(sizeZ-1)*(sizeX));     //!< Ez E coefficient

    long double time, timeStep, maxTime;   //!< Define advance in time.
    double cdtds;                          //!< Courant number (Maximal distance which can be traveled in a timestep)

    const double c = 2.99792458e8;
    const double epsilon_0 = 8.85418782e-12;
    const double Mu_0 = M_PI*4e-7;
  };
}
