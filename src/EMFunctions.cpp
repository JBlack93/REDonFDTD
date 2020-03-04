/* This Header File contains all the functions which call for global values
 * which therefore includes all the Electromagnetic effects
 */

#include <cmath>
#include "REDonFDTD/EMfunctions.hpp"

/* ELECTROMAGNETIC EFFECTS */

void REDonFDTD::timeAdvanceValues(Particle *p){
  p->prevPos[0]  = p->position[0];
  p->prevPos[1]  = p->position[1];
  p->prevPos[2]  = p->position[2];

  p->position[0] = p->futPos[0];
  p->position[1] = p->futPos[1];
  p->position[2] = p->futPos[2];

  p->prevVel[0]  = p->velocity[0];
  p->prevVel[1]  = p->velocity[1];
  p->prevVel[2]  = p->velocity[2];

  p->velocity[0] = p->futVel[0];
  p->velocity[1] = p->futVel[1];
  p->velocity[2] = p->futVel[2];

  p->prevAcc[0] = p->acceleration[0];
  p->prevAcc[1] = p->acceleration[1];
  p->prevAcc[2] = p->acceleration[2];

  p->acceleration[0] = p->futAcc[0];
  p->acceleration[1] = p->futAcc[1];
  p->acceleration[2] = p->futAcc[2];

  p->prevGamma = p->gamma;
  p->gamma = p->futGamma;
}

void REDonFDTD::halfTimeStep(Particle *p, Mesh *g){
  g->time += g->timeStep/2;
  p->newPositionTaylor(g);
  p->newVelocityTaylor(g);
  std::array<double,3> force = p->lorentzForce(g);
  p->findAcceleration(force);
  double powerRad = p->powerRadiated(g);
  if (powerRad !=0)   p->velocityAfterRad(g, powerRad);
  timeAdvanceValues(p);
}
