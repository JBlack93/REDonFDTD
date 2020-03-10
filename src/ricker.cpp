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
  velocity[0], velocity[1], velocity[2] = 0;
  acceleration[0], acceleration[1], acceleration[2] = 0;
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
