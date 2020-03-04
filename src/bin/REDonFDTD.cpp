/* 3D simulation with dipole source at center of mesh. */
#include <iostream>
#include <array>
#include <memory>

#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/ABC.hpp"
#include "REDonFDTD/output.hpp"
#include "REDonFDTD/EMfunctions.hpp"

using namespace REDonFDTD;

int main(){
  std::unique_ptr<Mesh> g = std::make_unique<Mesh>();// = std::make_unique<Mesh>(new Mesh);// = new Mesh;
  std::unique_ptr<Particle> p = std::make_unique<Particle>(g.get());

  initialiseABC(g.get());           // initialise ABC
  initialiseSlice(g.get());

  /* do time stepping */
  for (g->time = 0; g->time < g->maxTime; g->time = g->time){
    g->updateH();             // update magnetic fields in mesh
    halfTimeStep(p.get(), g.get());
    g->updateE();             // update electric fields in mesh
    //halfTimeStep(p.get(), g.get());
    p->sourceFunction(g.get());   // produce effects of source on local fields.
    updateABC(g.get());           // apply ABCs
    Slice(g.get());               // take a slice (if appropriate)
  }                     // end of time-stepping
  return 0;
}
