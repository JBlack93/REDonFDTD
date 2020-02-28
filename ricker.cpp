#include "macroSetUp.hpp"
#include "prototypes.hpp"
#include "stdio.h"

static double cdtds, ppw = 0;

/* initialize source-function variables */
void initialiseEzInc(Mesh *g)
{
    printf("Enter the points per wavelength for Ricker source: ");
    scanf(" %lf", &ppw);
    cdtds = Cdtds;
}

/* calculate source function at given time and location */
double ezInc(double time, double location)
{
    double arg;
    if (ppw <= 0)
    {
        fprintf(stderr,
        "ezInc: ezIncInit() must be called before ezInc.\n"
        "Points per wavelength must be positive.\n");
        exit(-1);
    }

    arg = M_PI * ((cdtds * time - location) / ppw - 1.0);
    arg = arg * arg;
    return (1.0 - 2.0 * arg) * exp(-arg);         // amplitude of change in field due to source
}

