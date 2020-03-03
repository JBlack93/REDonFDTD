/* The code used to implement a first-order ABC on each face of
 * the 3D domain.
 */
#include <cstdio>
#include "REDonFDTD/memAllocation.hpp"
#include "REDonFDTD/ABC.hpp"

/* global variables not visible outside of this package */
static double abccoef = 0.0;
static double *exy0, *exy1, *exz0, *exz1,
  *eyx0, *eyx1, *eyz0, *eyz1,
  *ezx0, *ezx1, *ezy0, *ezy1;

/* abc initialization function */
void initialiseABC(Mesh *g)
{
  abccoef = (g->cdtds - 1.0) / (g->cdtds + 1.0);

  /* allocate memory for ABC arrays */
  eyx0 = ALLOC_2D(eyx0, g->sizeY - 1, g->sizeZ);
  ezx0 = ALLOC_2D(ezx0, g->sizeY,     g->sizeZ-1);
  eyx1 = ALLOC_2D(eyx1, g->sizeY - 1, g->sizeZ);
  ezx1 = ALLOC_2D(ezx1, g->sizeY,     g->sizeZ-1);

  exy0 = ALLOC_2D(exy0, g->sizeX - 1, g->sizeZ);
  ezy0 = ALLOC_2D(ezy0, g->sizeX,     g->sizeZ-1);
  exy1 = ALLOC_2D(exy1, g->sizeX - 1, g->sizeZ);
  ezy1 = ALLOC_2D(ezy1, g->sizeX,     g->sizeZ-1);

  exz0 = ALLOC_2D(exz0, g->sizeX - 1, g->sizeY);
  eyz0 = ALLOC_2D(eyz0, g->sizeX,     g->sizeY-1);
  exz1 = ALLOC_2D(exz1, g->sizeX - 1, g->sizeY);
  eyz1 = ALLOC_2D(eyz1, g->sizeX,     g->sizeY-1);

  return;
} /* end initialiseABC() */



/* function that applies ABC -- called once per time step */
void updateABC(Mesh *g)
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
