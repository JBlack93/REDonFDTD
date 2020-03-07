#include <cstdio>
#include <cstdlib>

#include "REDonFDTD/source.hpp"
#include "REDonFDTD/ricker.hpp"
#include "REDonFDTD/utilities.hpp"

static double cdtds, ppw = 0;

/* initialize source-function variables */
REDonFDTD::ricker::ricker(Mesh *g){
  printf("Enter the points per wavelength for Ricker source: ");
  scanf(" %lf", &ppw);
  cdtds = g->cdtds;
}

void REDonFDTD::ricker::timeAdvanceValues(Mesh */*g*/){
  return;
}

std::array<double,3> REDonFDTD::ricker::eFieldProduced(Mesh *g, double x, double y, double z){
  std::array<double,3> vect{position[0]-x,position[1]-y,position[2]-z};
  const double eZ = ezInc(g->time, util::magnitude(vect));
  std::array<double,3> eField{0,0,eZ};
  return eField;
}

std::array<double,3> REDonFDTD::ricker::bFieldProduced(Mesh * /*g*/, std::array<double,3> /*eField*/,
                                                       double /*x*/, double /*y*/, double /*z*/){
  const std::array<double,3> bField{0,0,0};
  return bField;
}

/* calculate source function at given time and location */
double REDonFDTD::ricker::ezInc(double time, double location){
  double arg = M_PI * ((cdtds * time - location) / ppw - 1.0);
  arg = arg * arg;
  return (1.0 - 2.0 * arg) * exp(-arg);         // amplitude of change in field due to source
}
