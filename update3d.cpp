/* FUNCTIONS TO UPDATE THE FIELDS*/

#include "macroSetUp.hpp"
#include <stdio.h>


/* update magnetic field */
void updateH(Mesh *g)
{
    int mm, nn, pp;
    for (mm = 0; mm < SizeX; mm++)
    {
        for (nn = 0; nn < SizeY - 1; nn++)
        {
            for (pp = 0; pp < SizeZ - 1; pp++)
            {
                Hx(mm, nn, pp) = Chxh(mm, nn, pp) * Hx(mm, nn, pp) +
                                 Chxe(mm, nn, pp) * ((Ey(mm, nn, pp + 1) - Ey(mm, nn, pp)) -
                                 (Ez(mm, nn + 1, pp) - Ez(mm, nn, pp)));
            }
        }
    }

    for (mm = 0; mm < SizeX - 1; mm++)
    {
        for (nn = 0; nn < SizeY; nn++)
        {
            for (pp = 0; pp < SizeZ - 1; pp++)
            {
                Hy(mm, nn, pp) = Chyh(mm, nn, pp) * Hy(mm, nn, pp) +
                                 Chye(mm, nn, pp) * ((Ez(mm + 1, nn, pp) - Ez(mm, nn, pp)) -
                                 (Ex(mm, nn, pp + 1) - Ex(mm, nn, pp)));
            }
        }
    }
    for (mm = 0; mm < SizeX - 1; mm++)
    {
        for (nn = 0; nn < SizeY - 1; nn++)
        {
            for (pp = 0; pp < SizeZ; pp++)
            {
                Hz(mm, nn, pp) = Chzh(mm, nn, pp) * Hz(mm, nn, pp) +
                                 Chze(mm, nn, pp) * ((Ex(mm, nn + 1, pp) - Ex(mm, nn, pp)) -
                                 (Ey(mm + 1, nn, pp) - Ey(mm, nn, pp)));
            }
        }
    }

    return;
}                   /* end updateH() */





/* update electric field */
void updateE(Mesh *g)
{
    int mm, nn, pp;

    for (mm = 0; mm < SizeX - 1; mm++)
    {
        for (nn = 1; nn < SizeY - 1; nn++)
        {
            for (pp = 1; pp < SizeZ - 1; pp++)
            {
                Ex(mm, nn, pp) = Cexe(mm, nn, pp) * Ex(mm, nn, pp) +
                                     Cexh(mm, nn, pp) * ((Hz(mm, nn, pp) - Hz(mm, nn - 1, pp)) -
                                     (Hy(mm, nn, pp) - Hy(mm, nn, pp - 1)));
            }
        }
    }

    for (mm = 1; mm < SizeX - 1; mm++)
    {
        for (nn = 0; nn < SizeY - 1; nn++)
        {
            for (pp = 1; pp < SizeZ - 1; pp++)
            {
                Ey(mm, nn, pp) = Ceye(mm, nn, pp) * Ey(mm, nn, pp) +
                                     Ceyh(mm, nn, pp) * ((Hx(mm, nn, pp) - Hx(mm, nn, pp - 1)) -
                                     (Hz(mm, nn, pp) - Hz(mm - 1, nn, pp)));
            }
        }
    }

    for (mm = 1; mm < SizeX - 1; mm++)
    {
        for (nn = 1; nn < SizeY - 1; nn++)
        {
            for (pp = 0; pp < SizeZ - 1; pp++)
            {
                Ez(mm, nn, pp) = Ceze(mm, nn, pp) * Ez(mm, nn, pp) +
                                     Cezh(mm, nn, pp) * ((Hy(mm, nn, pp) - Hy(mm - 1, nn, pp)) -
                                     (Hx(mm, nn, pp) - Hx(mm, nn - 1, pp)));
            }
        }
    }

    return;

    }        /* end updateE() */



