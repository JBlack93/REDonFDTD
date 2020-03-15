/** @file mesh.hpp
 *  @brief Contains the Mesh class */
#pragma once

#include <cmath>
#include <vector>

#include "REDonFDTD/config.hpp"

namespace REDonFDTD {

//! @brief Mesh is the 4D space-time grid which contains both E and H fields.
  class Mesh {

  public:
    Mesh();
    Mesh(config configuration);
    ~Mesh() = default;

//! @brief Update the E-Field in the space-time Mesh
    void updateE();
//! @brief Update the H-Field in the space-time Mesh
    void updateH();

    int sizeX = 51;                                     //!< x-dimension of Mesh
    int sizeY = 50;                                     //!< y-dimension of Mesh
    int sizeZ = 50;                                     //!< z-dimension of Mesh
    int steps = 100;                                    //!< Number of Steps
    long double timeStep = 5e-10;                       //!< Duration of each step
    const long double cdtds = 1.0 / sqrt(3.0);          //!< Courant Number (see Eq: 4.13)
    const double c = 2.99792458e8;                      //!< Speed of light
    const double epsilon_0 = 8.85418782e-12;            //!< Permittivity of free space
    const double Mu_0 = M_PI*4e-7;                      //!< Magnetic Permeability
    double dS = c*timeStep/cdtds;                       //!< Grid Spacing
    long double maxTime = steps*timeStep;               //!< Duration of simulation


    std::vector<double> hx   = std::vector<double>(sizeX*(sizeY-1)*(sizeZ-1), 0);           //!< H_x field
    std::vector<double> chxh = std::vector<double>(sizeX*(sizeY-1)*(sizeZ-1), 1.0);         //!< Hx H coefficient
    std::vector<double> chxe = std::vector<double>(sizeX*(sizeY-1)*(sizeZ-1), cdtds/377.0); //!< Hx E coefficient

    std::vector<double> hy   = std::vector<double>(sizeZ*(sizeY-1)*(sizeX-1),0);            //!< H_y field
    std::vector<double> chyh = std::vector<double>(sizeZ*(sizeY-1)*(sizeX-1),1.0);          //!< Hy H coefficient
    std::vector<double> chye = std::vector<double>(sizeZ*(sizeY-1)*(sizeX-1), cdtds/377.0); //!< Hy E coefficient

    std::vector<double> hz   = std::vector<double>(sizeY*(sizeZ-1)*(sizeX-1),0);            //!< H_z field
    std::vector<double> chzh = std::vector<double>(sizeY*(sizeZ-1)*(sizeX-1),1.0);          //!< Hz H coefficient
    std::vector<double> chze = std::vector<double>(sizeY*(sizeZ-1)*(sizeX-1), cdtds/377.0); //!< Hz E coefficient

    std::vector<double> ex   = std::vector<double>(sizeZ*(sizeY)*(sizeX-1),0);              //!< E_x field
    std::vector<double> cexh = std::vector<double>(sizeZ*(sizeY)*(sizeX-1), cdtds*377.0);   //!< Ex H coefficient
    std::vector<double> cexe = std::vector<double>(sizeZ*(sizeY)*(sizeX-1),1.0);            //!< Ex E coefficient

    std::vector<double> ey   = std::vector<double>(sizeZ*(sizeY-1)*(sizeX),0);              //!< E_y field
    std::vector<double> ceyh = std::vector<double>(sizeZ*(sizeY-1)*(sizeX), cdtds*377.0);   //!< Ey H coefficient
    std::vector<double> ceye = std::vector<double>(sizeZ*(sizeY-1)*(sizeX),1.0);            //!< Ey E coefficient

    std::vector<double> ez   = std::vector<double>(sizeY*(sizeZ-1)*(sizeX),0);              //!< E_z field
    std::vector<double> cezh = std::vector<double>(sizeY*(sizeZ-1)*(sizeX), cdtds*377.0);   //!< Ez H coefficient
    std::vector<double> ceze = std::vector<double>(sizeY*(sizeZ-1)*(sizeX),1.0);            //!< Ez E coefficient

    long double time;          //!< Current time in simulation

/** @brief function that applies ABC -- called once per time step
 *  @param g        Space-time mesh to be updated
 */
    void updateABC();

    double abccoef;
    std::vector<double> eyx0 = std::vector<double>((sizeY-1)*sizeZ);
    std::vector<double> ezx0 = std::vector<double>(sizeY*(sizeZ-1));
    std::vector<double> eyx1 = std::vector<double>((sizeY-1)*sizeZ);
    std::vector<double> ezx1 = std::vector<double>(sizeY*(sizeZ-1));

    std::vector<double> exy0 = std::vector<double>((sizeX-1)*sizeZ);
    std::vector<double> ezy0 = std::vector<double>(sizeX*(sizeZ-1));
    std::vector<double> exy1 = std::vector<double>((sizeX-1)*sizeZ);
    std::vector<double> ezy1 = std::vector<double>(sizeX*(sizeZ-1));

    std::vector<double> exz0 = std::vector<double>((sizeX-1)*sizeY);
    std::vector<double> eyz0 = std::vector<double>(sizeX*(sizeY-1));
    std::vector<double> exz1 = std::vector<double>((sizeX-1)*sizeY);
    std::vector<double> eyz1 = std::vector<double>(sizeX*(sizeY-1));


  /** @brief External B field in Mesh */
  std::array<double,3> ExB;
  };
}
