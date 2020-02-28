/* 3D simulation with dipole source at center of mesh. */
#include <iostream>
#include <vector>
#include "include/REDonFDTD/prototypes.hpp"
#include "include/REDonFDTD/memAllocation.hpp"
#include "include/REDonFDTD/macroSetUp.hpp"
#include "include/REDonFDTD/particleInit.hpp"
#include "include/REDonFDTD/meshInit.hpp"

int main()
{
    Mesh *g;
    Particle *p;

    ALLOC_1D(g, 1, Mesh);       // allocate memory for mesh
    ALLOC_1D(p, 1, Particle);

    initialiseMesh(g);          // initialise 3D mesh
    initialiseABC(g);           // initialise ABC
    initialiseSlice(g);
    initialiseSource(p, g);


    /* do time stepping */
    for (Time = 0; Time < MaxTime; Time = Time)
    {
        updateH(g);             // update magnetic fields in mesh
        halfTimeStep(p, g);
        updateE(g);             // update electric fields in mesh
        //halfTimeStep(p, g);
        sourceFunction(p, g);   // produce effects of source on local fields.
        updateABC(g);           // apply ABCs
        Slice(g);               // take a slice (if appropriate)
    }                     // end of time-stepping
    return 0;
}
