/** @file meshInit.hpp
 *  @brief Contains the Mesh class */
#pragma once

#include <cmath>
#include "REDonFDTD/memAllocation.hpp"

//! @brief Mesh is the 4D space-time grid which contains both E and H fields.
class Mesh
{
public:
  Mesh(){
    double imp0 = 377.0;
    int mm, nn, pp;
    this->sizeX = 51;                       // size of domain
    this->sizeY = 50;
    this->sizeZ = 50;
    this->timeStep = 5*pow(10,-10);
    this->maxTime = 100*this->timeStep;           // duration of simulation
    this->cdtds = 1.0 / sqrt(3.0);          // Courant number

    /* memory allocation */
    this->hx = ALLOC_3D(this->hx,   this->sizeX,     this->sizeY - 1, this->sizeZ - 1);
    this->chxh = ALLOC_3D(this->chxh, this->sizeX,     this->sizeY - 1, this->sizeZ - 1);
    this->chxe = ALLOC_3D(this->chxe, this->sizeX,     this->sizeY - 1, this->sizeZ - 1);
    this->hy = ALLOC_3D(this->hy,   this->sizeX - 1, this->sizeY,     this->sizeZ - 1);
    this->chyh = ALLOC_3D(this->chyh, this->sizeX - 1, this->sizeY,     this->sizeZ - 1);
    this->chye = ALLOC_3D(this->chye, this->sizeX - 1, this->sizeY,     this->sizeZ - 1);
    this->hz = ALLOC_3D(this->hz,   this->sizeX - 1, this->sizeY - 1, this->sizeZ);
    this->chzh = ALLOC_3D(this->chzh, this->sizeX - 1, this->sizeY - 1, this->sizeZ);
    this->chze = ALLOC_3D(this->chze, this->sizeX - 1, this->sizeY - 1, this->sizeZ);


    this->ex = ALLOC_3D(this->ex,   this->sizeX - 1, this->sizeY,     this->sizeZ);
    this->cexe = ALLOC_3D(this->cexe, this->sizeX - 1, this->sizeY,     this->sizeZ);
    this->cexh = ALLOC_3D(this->cexh, this->sizeX - 1, this->sizeY,     this->sizeZ);
    this->ey = ALLOC_3D(this->ey,   this->sizeX,     this->sizeY - 1, this->sizeZ);
    this->ceye = ALLOC_3D(this->ceye, this->sizeX,     this->sizeY - 1, this->sizeZ);
    this->ceyh = ALLOC_3D(this->ceyh, this->sizeX,     this->sizeY - 1, this->sizeZ);
    this->ez = ALLOC_3D(this->ez,   this->sizeX,     this->sizeY,     this->sizeZ - 1);
    this->ceze = ALLOC_3D(this->ceze, this->sizeX,     this->sizeY,     this->sizeZ - 1);
    this->cezh = ALLOC_3D(this->cezh, this->sizeX,     this->sizeY,     this->sizeZ - 1);


    /* set electric-field update coefficients */
    for (mm = 0; mm < this->sizeX - 1; ++mm)
    {
      for (nn = 0; nn < this->sizeY; ++nn)
      {
        for (pp = 0; pp < this->sizeZ; ++pp)
        {
          this->cexe[(mm * (this->sizeY) + nn) * this->sizeZ + pp] = 1.0;
          this->cexh[(mm * (this->sizeY) + nn) * this->sizeZ + pp] = this->cdtds * imp0;
        }
      }
    }

    for (mm = 0; mm < this->sizeX; mm++)
    {
      for (nn = 0; nn < this->sizeY - 1; ++nn)
      {
        for (pp = 0; pp < this->sizeZ; ++pp)
        {
          this->ceye[(mm*(this->sizeY - 1) + nn) * this->sizeZ + pp] = 1.0;
          this->ceyh[(mm*(this->sizeY - 1) + nn) * this->sizeZ + pp] = this->cdtds * imp0;
        }
      }
    }


    for (mm = 0; mm < this->sizeX; ++mm)
    {
      for (nn = 0; nn < this->sizeY; ++nn)
      {
        for (pp = 0; pp < this->sizeZ - 1; ++pp)
        {
          this->ceze[(mm * (this->sizeY) + nn) * (this->sizeZ - 1) + pp] = 1.0;
          this->cezh[(mm * (this->sizeY) + nn) * (this->sizeZ - 1) + pp] = this->cdtds * imp0;
        }
      }
    }

    /* set magnetic-field update coefficients */
    for (mm = 0; mm < this->sizeX; ++mm)
    {
      for (nn = 0; nn < this->sizeY - 1; ++nn)
      {
        for (pp = 0; pp < this->sizeZ - 1; ++pp)
        {
          this->chxh[(mm * (this->sizeY - 1) + nn) * (this->sizeZ - 1) + pp] = 1.0;
          this->chxe[(mm * (this->sizeY - 1) + nn) * (this->sizeZ - 1) + pp] = this->cdtds / imp0;
        }
      }
    }

    for (mm = 0; mm < this->sizeX - 1; ++mm)
    {
      for (nn = 0; nn < this->sizeY; ++nn)
      {
        for (pp = 0; pp < this->sizeZ - 1; ++pp)
        {
          this->chyh[(mm * this->sizeY + nn) * (this->sizeZ - 1) + pp] = 1.0;
          this->chye[(mm * this->sizeY + nn) * (this->sizeZ - 1) + pp] = this->cdtds / imp0;
        }
      }
    }

    for (mm = 0; mm < this->sizeX - 1; ++mm)
    {
      for (nn = 0; nn < this->sizeY - 1; ++nn)
      {
        for (pp = 0; pp < this->sizeZ; ++pp)
        {
          this->chzh[(mm * (this->sizeY - 1) + nn) * this->sizeZ + pp] = 1.0;
          this->chze[(mm * (this->sizeY - 1) + nn) * this->sizeZ + pp] = this->cdtds / imp0;
        }
      }
    }

    return;
  }          /* end Mesh() */

  ~Mesh() = default;

  double *hx, *chxh, *chxe;              //!< H_x field. Plus coefficients needed in its Update equation
  double *hy, *chyh, *chye;              //!< H_y field. Plus coefficients needed in its Update equation
  double *hz, *chzh, *chze;              //!< H_z field. Plus coefficients needed in its Update equation
  double *ex, *cexe, *cexh;              //!< E_x field. Plus coefficients needed in its Update equation
  double *ey, *ceye, *ceyh;              //!< E_y field. Plus coefficients needed in its Update equation
  double *ez, *ceze, *cezh;              //!< E_z field. Plus coefficients needed in its Update equation
  int sizeX, sizeY, sizeZ;               //!<  Dimensions of the Mesh
  long double time, timeStep, maxTime;   //!< Define advance in time.
  double cdtds;                          //!< Courant number (Maximal distance which can be traveled in a timestep)

  double c = 2.99792458e8;
  double epsilon_0 = 8.85418782e-12;
  double Mu_0 = M_PI*4e-7;

};

// typedef class Mesh Mesh;
