/* FUNCTION TO INITIALISE A HOMOGENEOUS 3D MESH */

#include <iostream>
#include <math.h>
#include "include/REDonFDTD/macroSetUp.hpp"
#include "include/REDonFDTD/memAllocation.hpp"

 /* function to initialise the mesh */
void initialiseMesh(Mesh *g)
{
    double imp0 = 377.0;
    int mm, nn, pp;
    SizeX = 51;                       // size of domain
    SizeY = 50;
    SizeZ = 50;
    TimeStep = 5*pow(10,-10);
    MaxTime = 100*TimeStep;           // duration of simulation
    Cdtds = 1.0 / sqrt(3.0);          // Courant number

        /* memory allocation */
    ALLOC_3D(g->hx,   SizeX, SizeY - 1, SizeZ - 1, double);
    ALLOC_3D(g->chxh, SizeX, SizeY - 1, SizeZ - 1, double);
    ALLOC_3D(g->chxe, SizeX, SizeY - 1, SizeZ - 1, double);
    ALLOC_3D(g->hy,   SizeX - 1, SizeY, SizeZ - 1, double);
    ALLOC_3D(g->chyh, SizeX - 1, SizeY, SizeZ - 1, double);
    ALLOC_3D(g->chye, SizeX - 1, SizeY, SizeZ - 1, double);
    ALLOC_3D(g->hz,   SizeX - 1, SizeY - 1, SizeZ, double);
    ALLOC_3D(g->chzh, SizeX - 1, SizeY - 1, SizeZ, double);
    ALLOC_3D(g->chze, SizeX - 1, SizeY - 1, SizeZ, double);


    ALLOC_3D(g->ex,   SizeX - 1, SizeY, SizeZ, double);
    ALLOC_3D(g->cexe, SizeX - 1, SizeY, SizeZ, double);
    ALLOC_3D(g->cexh, SizeX - 1, SizeY, SizeZ, double);
    ALLOC_3D(g->ey,   SizeX, SizeY - 1, SizeZ, double);
    ALLOC_3D(g->ceye, SizeX, SizeY - 1, SizeZ, double);
    ALLOC_3D(g->ceyh, SizeX, SizeY - 1, SizeZ, double);
    ALLOC_3D(g->ez,   SizeX, SizeY, SizeZ - 1, double);
    ALLOC_3D(g->ceze, SizeX, SizeY, SizeZ - 1, double);
    ALLOC_3D(g->cezh, SizeX, SizeY, SizeZ - 1, double);


    /* set electric-field update coefficients */
    for (mm = 0; mm < SizeX - 1; mm++)
    {
       for (nn = 0; nn < SizeY; nn++)
        {
            for (pp = 0; pp < SizeZ; pp++)
            {
                Cexe(mm, nn, pp) = 1.0;
                Cexh(mm, nn, pp) = Cdtds * imp0;
            }
        }
    }

    for (mm = 0; mm < SizeX; mm++)
    {
        for (nn = 0; nn < SizeY - 1; nn++)
        {
            for (pp = 0; pp < SizeZ; pp++)
            {
                Ceye(mm, nn, pp) = 1.0;
                Ceyh(mm, nn, pp) = Cdtds * imp0;
            }
        }
    }


    for (mm = 0; mm < SizeX; mm++)
    {
        for (nn = 0; nn < SizeY; nn++)
        {
            for (pp = 0; pp < SizeZ - 1; pp++)
            {
                Ceze(mm, nn, pp) = 1.0;
                Cezh(mm, nn, pp) = Cdtds * imp0;
            }
        }
    }

    /* set magnetic-field update coefficients */
    for (mm = 0; mm < SizeX; mm++)
    {
        for (nn = 0; nn < SizeY - 1; nn++)
        {
            for (pp = 0; pp < SizeZ - 1; pp++)
            {
                Chxh(mm, nn, pp) = 1.0;
                Chxe(mm, nn, pp) = Cdtds / imp0;
            }
        }
    }

    for (mm = 0; mm < SizeX - 1; mm++)
    {
        for (nn = 0; nn < SizeY; nn++)
        {
            for (pp = 0; pp < SizeZ - 1; pp++)
            {
                Chyh(mm, nn, pp) = 1.0;
                Chye(mm, nn, pp) = Cdtds / imp0;
            }
        }
    }

    for (mm = 0; mm < SizeX - 1; mm++)
    {
        for (nn = 0; nn < SizeY - 1; nn++)
        {
            for (pp = 0; pp < SizeZ; pp++)
            {
                Chzh(mm, nn, pp) = 1.0;
                Chze(mm, nn, pp) = Cdtds / imp0;
            }
        }
    }

    return;
    }          /* end meshInit() */
