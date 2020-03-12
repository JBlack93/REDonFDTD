#include <cstdio>
#include <cstdlib>

#include <array>
#include "REDonFDTD/source.hpp"
#include "REDonFDTD/ricker.hpp"
#include "REDonFDTD/utilities.hpp"

/* initialize source-function variables */
REDonFDTD::ricker::ricker(Mesh *g, double pointspwave){
  position[0] = (static_cast<double>(g->sizeX)/2-0.05)*(g->dS);
  position[1] = (static_cast<double>(g->sizeY)/2-0.05)*(g->dS);
  position[2] = (static_cast<double>(g->sizeZ)/2-0.05)*(g->dS);
  ppw = pointspwave;
  findCell(g);
}

REDonFDTD::ricker::ricker(Mesh * g, config configuration){
  position[0] = configuration.position[0]*(g->dS);
  position[1] = configuration.position[1]*(g->dS);
  position[2] = configuration.position[2]*(g->dS);

  velocity[0] = configuration.velocity[0]*(g->c);
  velocity[1] = configuration.velocity[1]*(g->c);
  velocity[2] = configuration.velocity[2]*(g->c);

  acceleration = configuration.acceleration;

  ppw = configuration.ppw;

  findCell(g);
}


void REDonFDTD::ricker::timeAdvanceValues(Mesh */*g*/){
  return;
}

std::array<double,3> REDonFDTD::ricker::eFieldProduced(Mesh *g, double x, double y, double z){
  std::array<double,3> vect{position[0]-x,position[1]-y,position[2]-z};
  const double eZ = ezInc(g, util::magnitude(vect));
  std::array<double,3> eField{0,0,eZ};
  return eField;
}

std::array<double,3> REDonFDTD::ricker::bFieldProduced(Mesh * /*g*/, std::array<double,3> /*eField*/,
                                                       double /*x*/, double /*y*/, double /*z*/){
  const std::array<double,3> bField{0,0,0};
  return bField;
}

/* calculate source function at given time and location */
double REDonFDTD::ricker::ezInc(Mesh *g, double location){
  double arg = M_PI * ((g->cdtds * g->time - location) / ppw - 1.0);
  arg = arg * arg;
  return (1.0 - 2.0 * arg) * exp(-arg);         // amplitude of change in field due to source
}
