/* 3D simulation with dipole source at center of mesh. */
#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/geometry.hpp>

#include "prototypes.hpp"
#include "memAllocation.hpp"
#include "macroSetUp.hpp"
#include "particleInit.hpp"
#include "meshInit.hpp"


typedef boost::numeric::ublas::vector<double> vct;
using namespace boost::numeric::ublas;

//valgrind
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
