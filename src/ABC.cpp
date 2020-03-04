/* The code used to implement a first-order ABC on each face of
 * the 3D domain.
 */
#include <cstdio>
#include "REDonFDTD/ABC.hpp"

/* global variables not visible outside of this package */
static double abccoef = 0.0;

static std::vector<double> eyx0((y-1)*z);
static std::vector<double> ezx0(y*(z-1));
static std::vector<double> eyx1((y-1)*z);
static std::vector<double> ezx1(y*(z-1));

static std::vector<double> exy0((x-1)*z);
static std::vector<double> ezy0(x*(z-1));
static std::vector<double> exy1((x-1)*z);
static std::vector<double> ezy1(x*(z-1));

static std::vector<double> exz0((x-1)*y);
static std::vector<double> eyz0(x*(y-1));
static std::vector<double> exz1((x-1)*y);
static std::vector<double> eyz1(x*(y-1));

// /* abc initialization function */
void REDonFDTD::initialiseABC(Mesh *g){
  abccoef = (g->cdtds - 1.0) / (g->cdtds + 1.0);
}

/* function that applies ABC -- called once per time step */
void REDonFDTD::updateABC(Mesh *g)
{
  int mm, nn, pp;
  /* ABC at "x0" */
  mm = 0;
  for (nn = 0; nn < g->sizeY - 1; ++nn)
  {
    for (pp = 0; pp < g->sizeZ; ++pp)
    {
      g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp] =
        eyx0[nn*(g->sizeZ)+pp] + abccoef *
        (g->ey[((mm+1) * (g->sizeY - 1) + nn) * g->sizeZ + pp] -
         g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp]);

      eyx0[nn*(g->sizeZ)+pp] = g->ey[((mm+1) * (g->sizeY - 1) + nn) * g->sizeZ + pp];
    }
  }
  for (nn = 0; nn < g->sizeY; ++nn)
  {
    for (pp = 0; pp < g->sizeZ - 1; ++pp)
    {
      g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp] =
        ezx0[nn*(g->sizeZ-1)+pp] + abccoef *
        (g->ez[((mm+1)*(g->sizeY)+nn)*(g->sizeZ-1)+pp] -
         g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp]);
      ezx0[nn*(g->sizeZ-1)+pp] = g->ez[((mm+1)*(g->sizeY)+nn)*(g->sizeZ-1)+pp];
    }
  }

  /* ABC at "x1" */
  mm = g->sizeX - 1;

  for (nn = 0; nn < g->sizeY - 1; ++nn)
  {
    for (pp = 0; pp < g->sizeZ; ++pp)
    {
      g->ey[(mm*(g->sizeY-1)+nn)*(g->sizeZ)+pp] =
        eyx1[nn*(g->sizeZ)+pp] + abccoef *
        (g->ey[((mm-1)*(g->sizeY-1)+nn)*(g->sizeZ)+pp] -
         g->ey[(mm*(g->sizeY-1)+nn)*(g->sizeZ)+pp]);
      eyx1[nn*(g->sizeZ)+pp] = g->ey[((mm-1)*(g->sizeY-1)+nn)*(g->sizeZ)+pp];
    }
  }
  for (nn = 0; nn < g->sizeY; ++nn)
  {
    for (pp = 0; pp < g->sizeZ - 1; ++pp)
    {
      g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp] =
        ezx1[nn*(g->sizeZ-1)+pp] + abccoef *
        (g->ez[((mm-1)*(g->sizeY)+nn)*(g->sizeZ-1)+pp] -
         g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp]);
      ezx1[nn*(g->sizeZ-1)+pp] = g->ez[((mm-1)*(g->sizeY)+nn)*(g->sizeZ-1)+pp];
    }
  }

  /* ABC at "y0" */
  nn = 0;
  for (mm = 0; mm < g->sizeX - 1; ++mm)
  {
    for (pp = 0; pp < g->sizeZ; ++pp)
    {
      g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp] =
        exy0[mm*(g->sizeZ)+pp] + abccoef *
        (g->ex[(mm*(g->sizeY)+nn+1)*(g->sizeZ)+pp] -
         g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp]);
      exy0[mm*(g->sizeZ)+pp] = g->ex[(mm*(g->sizeY)+nn+1)*(g->sizeZ)+pp];
    }
  }

  for (mm = 0; mm < g->sizeX; ++mm)
  {
    for (pp = 0; pp < g->sizeZ - 1; ++pp)
    {
      g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp] =
        ezy0[mm*(g->sizeZ-1)+pp] + abccoef *
        (g->ez[(mm*(g->sizeY)+nn+1)*(g->sizeZ-1)+pp] -
         g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp]);
      ezy0[mm*(g->sizeZ-1)+pp] = g->ez[(mm*(g->sizeY)+nn+1)*(g->sizeZ-1)+pp];
    }
  }


  /* ABC at "y1" */
  nn = g->sizeY - 1;
  for (mm = 0; mm < g->sizeX - 1; ++mm)
  {
    for (pp = 0; pp < g->sizeZ; ++pp)
    {
      g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp] =
        exy1[mm*(g->sizeZ)+pp] + abccoef *
        (g->ex[(mm*(g->sizeY)+nn-1)*(g->sizeZ)+pp] -
         g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp]);
      exy1[mm*(g->sizeZ)+pp] = g->ex[(mm*(g->sizeY)+nn-1)*(g->sizeZ)+pp];
    }
  }
  for (mm = 0; mm < g->sizeX; ++mm)
  {
    for (pp = 0; pp < g->sizeZ - 1; ++pp)
    {
      g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp] =
        ezy1[mm*(g->sizeZ-1)+pp] + abccoef *
        (g->ez[(mm*(g->sizeY)+nn-1)*(g->sizeZ-1)+pp] -
         g->ez[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+pp]);
      ezy1[mm*(g->sizeZ-1)+pp] = g->ez[(mm*(g->sizeY)+nn-1)*(g->sizeZ-1)+pp];
    }
  }

  /* ABC at "z0" (bottom) */
  pp = 0;
  for (mm = 0; mm < g->sizeX - 1; ++mm)
  {
    for (nn = 0; nn < g->sizeY; ++nn)
    {
      g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp] =
        exz0[mm*(g->sizeY)+nn] + abccoef *
        (g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp+1] -
         g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp]);
      exz0[mm*(g->sizeY)+nn] = g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp+1];
    }
  }
  for (mm = 0; mm < g->sizeX; ++mm)
  {
    for (nn = 0; nn < g->sizeY - 1; ++nn)
    {
      g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp] =
        eyz0[mm*(g->sizeY-1)+nn] + abccoef *
        (g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp+1] -
         g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp]);
      eyz0[mm*(g->sizeY-1)+nn] = g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp+1];
    }
  }

  /* ABC at "z1" (top) */
  pp = g->sizeZ - 1;
  for (mm = 0; mm < g->sizeX - 1; ++mm)
  {
    for (nn = 0; nn < g->sizeY; ++nn)
    {
      g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp] =
        exz1[mm*(g->sizeY)+nn] + abccoef *
        (g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp-1] -
         g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp]);
      exz1[mm*(g->sizeY)+nn] = g->ex[(mm*(g->sizeY)+nn)*(g->sizeZ)+pp-1];
    }
  }
  for (mm = 0; mm < g->sizeX; ++mm)
  {
    for (nn = 0; nn < g->sizeY - 1; ++nn)
    {
      g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp] =
        eyz1[mm*(g->sizeY - 1)+nn] + abccoef *
        (g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp-1] -
         g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp]);
      eyz1[mm*(g->sizeY - 1)+nn] = g->ey[((mm) * (g->sizeY - 1) + nn) * g->sizeZ + pp-1];
    }
  }
  return;
}                   /* end updateABC() */
