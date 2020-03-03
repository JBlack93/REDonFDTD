/* FUNCTIONS TO UPDATE THE FIELDS*/

#include <stdio.h>
#include "REDonFDTD/meshInit.hpp"


/* update magnetic field */
void Mesh::updateH(Mesh *g)
{
    int mm, nn, pp;
    for (mm = 0; mm < g->sizeX; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
                g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] = g->chxh[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] * g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] +
                                 g->chxe[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] * ((g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp+1] - g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp]) -
                                 (g->ez[(mm*g->sizeY+nn+1)*(g->sizeZ-1)+pp] - g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp]));
            }
        }
    }

    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
                g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] = g->chyh[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] +
                  g->chye[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * ((g->ez[((mm+1)*g->sizeY+nn)*(g->sizeZ-1)+pp] - g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp]) -
                                 (g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp+1] - g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp]));
            }
        }
    }
    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ; ++pp)
            {
                g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] = g->chzh[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] +
                  g->chze[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * ((g->ex[(mm*g->sizeY+nn+1)*g->sizeZ+pp] - g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp]) -
                                                     (g->ey[((mm+1)*(g->sizeY-1)+nn)*g->sizeZ+pp] - g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp]));
            }
        }
    }

    return;
}                   /* end updateH() */





/* update electric field */
void Mesh::updateE(Mesh *g)
{
    int mm, nn, pp;

    for (mm = 0; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 1; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 1; pp < g->sizeZ - 1; ++pp)
            {
                g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp] = g->cexe[(mm*g->sizeY+nn)*g->sizeZ+pp] * g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp] +
                                     g->cexh[(mm*g->sizeY+nn)*g->sizeZ+pp] * ((g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] - g->hz[(mm*(g->sizeY-1)+nn-1)*g->sizeZ+pp]) -
                                     (g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] - g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp-1]));
            }
        }
    }

    for (mm = 1; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 0; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 1; pp < g->sizeZ - 1; ++pp)
            {
                g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] = g->ceye[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] +
                  g->ceyh[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * ((g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] - (g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+(pp-1)]) -
                                       (g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] - g->hz[((mm-1)*(g->sizeY-1)+nn)*g->sizeZ+pp])));
            }
        }
    }

    for (mm = 1; mm < g->sizeX - 1; ++mm)
    {
        for (nn = 1; nn < g->sizeY - 1; ++nn)
        {
            for (pp = 0; pp < g->sizeZ - 1; ++pp)
            {
                g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] = g->ceze[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] +
                  g->cezh[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * ((g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] - g->hy[((mm-1)*g->sizeY+nn)*(g->sizeZ-1)+pp]) -
                                     (g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] - g->hx[(mm*(g->sizeY-1)+nn-1)*(g->sizeZ-1)+pp]));
            }
        }
    }

    return;

    }        /* end updateE() */
