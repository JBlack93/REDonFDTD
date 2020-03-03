/* 3D simulation with dipole source at center of mesh. */
#include <iostream>
#include <vector>

#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/ABC.hpp"
#include "REDonFDTD/output.hpp"
#include "REDonFDTD/EMfunctions.hpp"

int main()
{
  Mesh * g = new Mesh;

  initialiseABC(g);           // initialise ABC
  initialiseSlice(g);

  Particle * p = new Particle(g);

  /* do time stepping */
  for (g->time = 0; g->time < g->maxTime; g->time = g->time)
  {
    g->updateH(g);             // update magnetic fields in mesh
    halfTimeStep(p, g);
    g->updateE(g);             // update electric fields in mesh
    //halfTimeStep(p, g);
    p->sourceFunction(g);   // produce effects of source on local fields.
    updateABC(g);           // apply ABCs
    Slice(g);               // take a slice (if appropriate)
  }                     // end of time-stepping
  return 0;
}
