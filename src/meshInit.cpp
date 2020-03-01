/* FUNCTION TO INITIALISE A HOMOGENEOUS 3D MESH */

#include <iostream>
#include <cmath>
#include "REDonFDTD/macroSetUp.hpp"
#include "REDonFDTD/memAllocation.hpp"

 /* function to initialise the mesh */
void initialiseMesh(Mesh *g)
{
    double imp0 = 377.0;
    int mm, nn, pp;
    g->sizeX = 51;                       // size of domain
    g->sizeY = 50;
    g->sizeZ = 50;
    g->timeStep = 5*pow(10,-10);
    g->maxTime = 100*g->timeStep;           // duration of simulation
    g->cdtds = 1.0 / sqrt(3.0);          // Courant number

        /* memory allocation */
    ALLOC_3D(g->hx,   g->sizeX,     g->sizeY - 1, g->sizeZ - 1, double);
    ALLOC_3D(g->chxh, g->sizeX,     g->sizeY - 1, g->sizeZ - 1, double);
    ALLOC_3D(g->chxe, g->sizeX,     g->sizeY - 1, g->sizeZ - 1, double);
    ALLOC_3D(g->hy,   g->sizeX - 1, g->sizeY,     g->sizeZ - 1, double);
    ALLOC_3D(g->chyh, g->sizeX - 1, g->sizeY,     g->sizeZ - 1, double);
    ALLOC_3D(g->chye, g->sizeX - 1, g->sizeY,     g->sizeZ - 1, double);
    ALLOC_3D(g->hz,   g->sizeX - 1, g->sizeY - 1, g->sizeZ,     double);
    ALLOC_3D(g->chzh, g->sizeX - 1, g->sizeY - 1, g->sizeZ,     double);
    ALLOC_3D(g->chze, g->sizeX - 1, g->sizeY - 1, g->sizeZ,     double);


    ALLOC_3D(g->ex,   g->sizeX - 1, g->sizeY,     g->sizeZ,     double);
    ALLOC_3D(g->cexe, g->sizeX - 1, g->sizeY,     g->sizeZ,     double);
    ALLOC_3D(g->cexh, g->sizeX - 1, g->sizeY,     g->sizeZ,     double);
    ALLOC_3D(g->ey,   g->sizeX,     g->sizeY - 1, g->sizeZ,     double);
    ALLOC_3D(g->ceye, g->sizeX,     g->sizeY - 1, g->sizeZ,     double);
    ALLOC_3D(g->ceyh, g->sizeX,     g->sizeY - 1, g->sizeZ,     double);
    ALLOC_3D(g->ez,   g->sizeX,     g->sizeY,     g->sizeZ - 1, double);
    ALLOC_3D(g->ceze, g->sizeX,     g->sizeY,     g->sizeZ - 1, double);
    ALLOC_3D(g->cezh, g->sizeX,     g->sizeY,     g->sizeZ - 1, double);


    /* set electric-field update coefficients */
    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
       for (nn = 0; nn < g->sizeY; ++nn)
        {
            for (pp = 0; pp < g->sizeZ; ++pp)
            {
                Cexe(mm, nn, pp) = 1.0;
                Cexh(mm, nn, pp) = g->cdtds * imp0;
            }
        }
    }

    for (mm = 0; mm < g->sizeX; mm++)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ; ++pp)
            {
                Ceye(mm, nn, pp) = 1.0;
                Ceyh(mm, nn, pp) = g->cdtds * imp0;
            }
        }
    }


    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (nn = 0; nn < g->sizeY; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
                Ceze(mm, nn, pp) = 1.0;
                Cezh(mm, nn, pp) = g->cdtds * imp0;
            }
        }
    }

    /* set magnetic-field update coefficients */
    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
                Chxh(mm, nn, pp) = 1.0;
                Chxe(mm, nn, pp) = g->cdtds / imp0;
            }
        }
    }

    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
                Chyh(mm, nn, pp) = 1.0;
                Chye(mm, nn, pp) = g->cdtds / imp0;
            }
        }
    }

    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ; ++pp)
            {
                Chzh(mm, nn, pp) = 1.0;
                Chze(mm, nn, pp) = g->cdtds / imp0;
            }
        }
    }

    return;
    }          /* end meshInit() */
