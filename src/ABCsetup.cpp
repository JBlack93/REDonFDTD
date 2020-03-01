/* The code used to implement a first-order ABC on each face of
 * the 3D domain.
 */
#include <stdio.h>
#include "REDonFDTD/memAllocation.hpp"
#include "REDonFDTD/macroSetUp.hpp"

/* Macros to access stored "old" value */
#define Eyx0(N, P) eyx0[(N) * (g->sizeZ)     + (P)]
#define Ezx0(N, P) ezx0[(N) * (g->sizeZ - 1) + (P)]
#define Eyx1(N, P) eyx1[(N) * (g->sizeZ)     + (P)]
#define Ezx1(N, P) ezx1[(N) * (g->sizeZ - 1) + (P)]

#define Exy0(M, P) exy0[(M) * (g->sizeZ)     + (P)]
#define Ezy0(M, P) ezy0[(M) * (g->sizeZ - 1) + (P)]
#define Exy1(M, P) exy1[(M) * (g->sizeZ)     + (P)]
#define Ezy1(M, P) ezy1[(M) * (g->sizeZ - 1) + (P)]

#define Exz0(M, N) exz0[(M) * (g->sizeY)     + (N)]
#define Eyz0(M, N) eyz0[(M) * (g->sizeY - 1) + (N)]
#define Exz1(M, N) exz1[(M) * (g->sizeY)     + (N)]
#define Eyz1(M, N) eyz1[(M) * (g->sizeY - 1) + (N)]

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
    ALLOC_2D(eyx0, g->sizeY - 1, g->sizeZ,     double);
    ALLOC_2D(ezx0, g->sizeY,     g->sizeZ - 1, double);
    ALLOC_2D(eyx1, g->sizeY - 1, g->sizeZ,     double);
    ALLOC_2D(ezx1, g->sizeY,     g->sizeZ - 1, double);

    ALLOC_2D(exy0, g->sizeX - 1, g->sizeZ,     double);
    ALLOC_2D(ezy0, g->sizeX,     g->sizeZ - 1, double);
    ALLOC_2D(exy1, g->sizeX - 1, g->sizeZ,     double);
    ALLOC_2D(ezy1, g->sizeX,     g->sizeZ - 1, double);

    ALLOC_2D(exz0, g->sizeX - 1, g->sizeY,     double);
    ALLOC_2D(eyz0, g->sizeX,     g->sizeY - 1, double);
    ALLOC_2D(exz1, g->sizeX - 1, g->sizeY,     double);
    ALLOC_2D(eyz1, g->sizeX,     g->sizeY - 1, double);

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
            Ey(mm, nn, pp) = Eyx0(nn, pp) +
                             abccoef * (Ey(mm + 1, nn, pp) - Ey(mm, nn, pp));
            Eyx0(nn, pp) = Ey(mm + 1, nn, pp);
        }
    }
    for (nn = 0; nn < g->sizeY; ++nn)
    {
        for (pp = 0; pp < g->sizeZ - 1; ++pp)
        {
            Ez(mm, nn, pp) = Ezx0(nn, pp) +
                             abccoef * (Ez(mm + 1, nn, pp) - Ez(mm, nn, pp));
            Ezx0(nn, pp) = Ez(mm + 1, nn, pp);
        }
    }

    /* ABC at "x1" */
    mm = g->sizeX - 1;

    for (nn = 0; nn < g->sizeY - 1; ++nn)
    {
        for (pp = 0; pp < g->sizeZ; ++pp)
        {
            Ey(mm, nn, pp) = Eyx1(nn, pp) +
                             abccoef * (Ey(mm - 1, nn, pp) - Ey(mm, nn, pp));
            Eyx1(nn, pp) = Ey(mm - 1, nn, pp);
        }
    }
    for (nn = 0; nn < g->sizeY; ++nn)
    {
        for (pp = 0; pp < g->sizeZ - 1; ++pp)
        {
            Ez(mm, nn, pp) = Ezx1(nn, pp) +
                             abccoef * (Ez(mm - 1, nn, pp) - Ez(mm, nn, pp));
            Ezx1(nn, pp) = Ez(mm - 1, nn, pp);
        }
    }



    /* ABC at "y0" */
    nn = 0;
    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (pp = 0; pp < g->sizeZ; ++pp)
        {
            Ex(mm, nn, pp) = Exy0(mm, pp) +
                             abccoef * (Ex(mm, nn + 1, pp) - Ex(mm, nn, pp));
            Exy0(mm, pp) = Ex(mm, nn + 1, pp);
        }
    }

    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (pp = 0; pp < g->sizeZ - 1; ++pp)
        {
            Ez(mm, nn, pp) = Ezy0(mm, pp) +
                             abccoef * (Ez(mm, nn + 1, pp) - Ez(mm, nn, pp));
            Ezy0(mm, pp) = Ez(mm, nn + 1, pp);
        }
    }


    /* ABC at "y1" */
    nn = g->sizeY - 1;
    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (pp = 0; pp < g->sizeZ; ++pp)
        {
            Ex(mm, nn, pp) = Exy1(mm, pp) +
                             abccoef * (Ex(mm, nn - 1, pp) - Ex(mm, nn, pp));
            Exy1(mm, pp) = Ex(mm, nn - 1, pp);
        }
    }
    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (pp = 0; pp < g->sizeZ - 1; ++pp)
        {
            Ez(mm, nn, pp) = Ezy1(mm, pp) +
                             abccoef * (Ez(mm, nn - 1, pp) - Ez(mm, nn, pp));
            Ezy1(mm, pp) = Ez(mm, nn - 1, pp);
        }
    }

    /* ABC at "z0" (bottom) */
    pp = 0;
    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY; ++nn)
        {
            Ex(mm, nn, pp) = Exz0(mm, nn) +
                             abccoef * (Ex(mm, nn, pp + 1) - Ex(mm, nn, pp));
            Exz0(mm, nn) = Ex(mm, nn, pp + 1);
        }
    }
    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
        Ey(mm, nn, pp) = Eyz0(mm, nn) +
                         abccoef * (Ey(mm, nn, pp + 1) - Ey(mm, nn, pp));
        Eyz0(mm, nn) = Ey(mm, nn, pp + 1);
        }
    }

    /* ABC at "z1" (top) */
    pp = g->sizeZ - 1;
    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY; ++nn)
        {
            Ex(mm, nn, pp) = Exz1(mm, nn) +
                             abccoef * (Ex(mm, nn, pp - 1) - Ex(mm, nn, pp));
            Exz1(mm, nn) = Ex(mm, nn, pp - 1);
        }
    }
    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            Ey(mm, nn, pp) = Eyz1(mm, nn) +
                             abccoef * (Ey(mm, nn, pp - 1) - Ey(mm, nn, pp));
            Eyz1(mm, nn) = Ey(mm, nn, pp - 1);
        }
    }
    return;
}                   /* end updateABC() */
