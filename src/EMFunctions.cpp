/* This Header File contains all the functions which call for global values
 * which therefore includes all the Electromagnetic effects
 */

#include <cmath>
#include "REDonFDTD/EMfunctions.hpp"

/* ELECTROMAGNETIC EFFECTS */

void REDonFDTD::halfTimeStep(Particle *p, Mesh *g){
  g->time += g->timeStep/2;
  p->newPositionTaylor(g);
  p->newVelocityTaylor(g);
  std::array<double,3> force = p->lorentzForce(g);
  p->findAcceleration(force);
  const double powerRad = p->powerRadiated(g);
  if (powerRad !=0)   p->velocityAfterRad(g, powerRad);
  p->timeAdvanceValues();
}
