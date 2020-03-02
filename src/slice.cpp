#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "REDonFDTD/prototypes.hpp"

static int temporalStride = -2, startTime;

void initialiseSlice(Mesh *g)
{
    int choice;
    printf("Do you want 2D slices of the 3D grid? (1=yes, 0=no) ");
    scanf("%d", &choice);
    if (choice == 0)
    {
        temporalStride = -1;
        return;
    }

    remove( "dimensions1.txt" );
    remove( "dimensions2.txt" );
    remove( "ExXZ.txt" );
    remove( "ExYZ.txt" );
    int numberSteps = (g->maxTime)/(g->timeStep);
    printf("Duration of simulation is %d steps.\n", numberSteps);
    printf("Enter start time and temporal stride: ");
    scanf(" %d %d", &startTime, &temporalStride);
    return;
    }        /* end initialiseSlice() */



void Slice(Mesh *g)
{
    using namespace std;
    ofstream myfile;

    int mm, nn, pp;
    float dim1, dim2, temp;

    /* ensure temporal stride set to a reasonable value */
    if (temporalStride == -1)   return;

    if (temporalStride < -1)
    {
        fprintf(stderr,
        "Slice: initialiseSlice must be called before Slice.\n"
        "Temporal stride must be set to positive value.\n");
        exit(-1);
    }


    int arg = (int) (g->time - startTime)/(g->timeStep);
    /* get snapshot if temporal conditions met */
    if (g->time >= startTime && arg % temporalStride == 0)
    {

        /************ write the constant-x slice ************/

        /* write dimensions to output file */
        dim1 = g->sizeY;                // express dimensions as floats
        dim2 = g->sizeZ;                // express dimensions as floats
        writeSingleValue(dim1, "dimensions1.txt", 1);
        writeSingleValue(dim2, "dimensions1.txt", 1);
        writeSingleValue(g->maxTime, "dimensions1.txt",1);
        writeSingleValue(g->timeStep, "dimensions1.txt", 1);
        /* write remaining data */
        mm = (g->sizeX - 1) / 2;
        for (pp = 0; pp < g->sizeZ; ++pp)
        {
            for (nn = 0; nn < g->sizeY; ++nn)
            {
              temp = (float) g->ex[(mm * (g->sizeY) + nn) * (g->sizeZ) + pp];         // store data as a float
                writeSingleValue(temp, "ExYZ.txt", 1);  // write out float value
            }
        }
    }              // close file

    /************ write the constant-y slice ************/

    /* write dimensions to output file */
    dim1 = g->sizeX - 1;                 // express dimensions as floats
    dim2 = g->sizeZ;                     // express dimensions as floats
    writeSingleValue(dim1, "dimensions2.txt", 1);
    writeSingleValue(dim2, "dimensions2.txt", 1);
    writeSingleValue(g->maxTime, "dimensions2.txt",1);
    writeSingleValue(g->timeStep, "dimensions2.txt", 1);
    /* write remaining data */
    nn = g->sizeY / 2;
    for (pp = 0; pp < g->sizeZ; ++pp)
    {
        for (mm = 0; mm < g->sizeX - 1; ++mm)
        {
            temp = (float) g->ex[(mm * (g->sizeY) + nn) * (g->sizeZ) + pp];         // store data as a float
            writeSingleValue(temp, "ExXZ.txt", 1);   // write the float
        }
    }
    return;
} /* end Slice() */
