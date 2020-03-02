/* FUNCTION TO INITIALISE A HOMOGENEOUS 3D MESH */

#include <iostream>
#include <cmath>
#include "REDonFDTD/memAllocation.hpp"
#include "REDonFDTD/meshInit.hpp"

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
    g->hx = ALLOC_3D(g->hx,   g->sizeX,     g->sizeY - 1, g->sizeZ - 1);
    g->chxh = ALLOC_3D(g->chxh, g->sizeX,     g->sizeY - 1, g->sizeZ - 1);
    g->chxe = ALLOC_3D(g->chxe, g->sizeX,     g->sizeY - 1, g->sizeZ - 1);
    g->hy = ALLOC_3D(g->hy,   g->sizeX - 1, g->sizeY,     g->sizeZ - 1);
    g->chyh = ALLOC_3D(g->chyh, g->sizeX - 1, g->sizeY,     g->sizeZ - 1);
    g->chye = ALLOC_3D(g->chye, g->sizeX - 1, g->sizeY,     g->sizeZ - 1);
    g->hz = ALLOC_3D(g->hz,   g->sizeX - 1, g->sizeY - 1, g->sizeZ);
    g->chzh = ALLOC_3D(g->chzh, g->sizeX - 1, g->sizeY - 1, g->sizeZ);
    g->chze = ALLOC_3D(g->chze, g->sizeX - 1, g->sizeY - 1, g->sizeZ);


    g->ex = ALLOC_3D(g->ex,   g->sizeX - 1, g->sizeY,     g->sizeZ);
    g->cexe = ALLOC_3D(g->cexe, g->sizeX - 1, g->sizeY,     g->sizeZ);
    g->cexh = ALLOC_3D(g->cexh, g->sizeX - 1, g->sizeY,     g->sizeZ);
    g->ey = ALLOC_3D(g->ey,   g->sizeX,     g->sizeY - 1, g->sizeZ);
    g->ceye = ALLOC_3D(g->ceye, g->sizeX,     g->sizeY - 1, g->sizeZ);
    g->ceyh = ALLOC_3D(g->ceyh, g->sizeX,     g->sizeY - 1, g->sizeZ);
    g->ez = ALLOC_3D(g->ez,   g->sizeX,     g->sizeY,     g->sizeZ - 1);
    g->ceze = ALLOC_3D(g->ceze, g->sizeX,     g->sizeY,     g->sizeZ - 1);
    g->cezh = ALLOC_3D(g->cezh, g->sizeX,     g->sizeY,     g->sizeZ - 1);


    /* set electric-field update coefficients */
    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
       for (nn = 0; nn < g->sizeY; ++nn)
        {
            for (pp = 0; pp < g->sizeZ; ++pp)
            {
              g->cexe[(mm * (g->sizeY) + nn) * g->sizeZ + pp] = 1.0;
              g->cexh[(mm * (g->sizeY) + nn) * g->sizeZ + pp] = g->cdtds * imp0;
            }
        }
    }

    for (mm = 0; mm < g->sizeX; mm++)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ; ++pp)
            {
                g->ceye[(mm*(g->sizeY - 1) + nn) * g->sizeZ + pp] = 1.0;
                g->ceyh[(mm*(g->sizeY - 1) + nn) * g->sizeZ + pp] = g->cdtds * imp0;
            }
        }
    }


    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (nn = 0; nn < g->sizeY; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
              g->ceze[(mm * (g->sizeY) + nn) * (g->sizeZ - 1) + pp] = 1.0;
              g->cezh[(mm * (g->sizeY) + nn) * (g->sizeZ - 1) + pp] = g->cdtds * imp0;
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
                g->chxh[(mm * (g->sizeY - 1) + nn) * (g->sizeZ - 1) + pp] = 1.0;
                g->chxe[(mm * (g->sizeY - 1) + nn) * (g->sizeZ - 1) + pp] = g->cdtds / imp0;
            }
        }
    }

    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
                g->chyh[(mm * g->sizeY + nn) * (g->sizeZ - 1) + pp] = 1.0;
                g->chye[(mm * g->sizeY + nn) * (g->sizeZ - 1) + pp] = g->cdtds / imp0;
            }
        }
    }

    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ; ++pp)
            {
                g->chzh[(mm * (g->sizeY - 1) + nn) * g->sizeZ + pp] = 1.0;
                g->chze[(mm * (g->sizeY - 1) + nn) * g->sizeZ + pp] = g->cdtds / imp0;
            }
        }
    }

    return;
    }          /* end meshInit() */
