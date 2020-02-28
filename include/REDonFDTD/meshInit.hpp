/** @file meshInit.hpp
 *  @brief Contains the Mesh struct */
#ifndef _MESH_INIT_H
#define _MESH_INIT_H

//! @brief Mesh is the 4D space-time grid which contains both E and H fields.
struct Mesh
{
    double *hx, *chxh, *chxe;              //!< H_x field. Plus coefficients needed in its Update equation
    double *hy, *chyh, *chye;              //!< H_y field. Plus coefficients needed in its Update equation
    double *hz, *chzh, *chze;              //!< H_z field. Plus coefficients needed in its Update equation
    double *ex, *cexe, *cexh;              //!< E_x field. Plus coefficients needed in its Update equation
    double *ey, *ceye, *ceyh;              //!< E_y field. Plus coefficients needed in its Update equation
    double *ez, *ceze, *cezh;              //!< E_z field. Plus coefficients needed in its Update equation
    int sizeX, sizeY, sizeZ;               //!<  Dimensions of the Mesh
    long double time, timeStep, maxTime;   //!< Define advance in time.
    double cdtds;                          //!< Courant number (Maximal distance which can be traveled in a timestep)
};

typedef struct Mesh Mesh;

#endif
