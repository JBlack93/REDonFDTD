#include <stdio.h>
#include <stdlib.h>
#include "macroSetUp.hpp"
#include <fstream>
#include "prototypes.hpp"

static int temporalStride = -2, frameX = 0, frameY = 0, startTime;
static char basename[80];

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
    int numberSteps = MaxTime/TimeStep;
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
    if (temporalStride == -1)
    {
        return;
    }

    if (temporalStride < -1)
    {
        fprintf(stderr,
        "snapshot3d: initialiseSnapshot must be called before snapshot.\n"
        "Temporal stride must be set to positive value.\n");
        exit(-1);
    }


    int arg = (int) (Time - startTime)/TimeStep;
    /* get snapshot if temporal conditions met */
    if (Time >= startTime && arg % temporalStride == 0)
    {

        /************ write the constant-x slice ************/

        /* write dimensions to output file */
        dim1 = SizeY;                // express dimensions as floats
        dim2 = SizeZ;                // express dimensions as floats
        writeSingleValue(dim1, "dimensions1.txt", 1);
        writeSingleValue(dim2, "dimensions1.txt", 1);
        writeSingleValue(MaxTime, "dimensions1.txt",1);
        writeSingleValue(TimeStep, "dimensions1.txt", 1);
        /* write remaining data */
        mm = (SizeX - 1) / 2;
        for (pp = 0; pp < SizeZ; pp++)
        {
            for (nn = 0; nn < SizeY; nn++)
            {
                temp = (float)Ex(mm, nn, pp);         // store data as a float
                writeSingleValue(temp, "ExYZ.txt", 1);  // write out float value
            }
        }
    }              // close file

    /************ write the constant-y slice ************/

    /* write dimensions to output file */
    dim1 = SizeX - 1;                 // express dimensions as floats
    dim2 = SizeZ;                     // express dimensions as floats
    writeSingleValue(dim1, "dimensions2.txt", 1);
    writeSingleValue(dim2, "dimensions2.txt", 1);
    writeSingleValue(MaxTime, "dimensions2.txt",1);
    writeSingleValue(TimeStep, "dimensions2.txt", 1);
    /* write remaining data */
    nn = SizeY / 2;
    for (pp = 0; pp < SizeZ; pp++)
    {
        for (mm = 0; mm < SizeX - 1; mm++)
        {
            temp = (float)Ex(mm, nn, pp);         // store data as a float
            writeSingleValue(temp, "ExXZ.txt", 1);   // write the float
        }
    }
    return;
} /* end Slice() */
