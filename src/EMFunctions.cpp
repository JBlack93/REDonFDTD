/* This Header File contains all the functions which call for global values
 * which therefore includes all the Electromagnetic effects
 */

#include <cmath>
#include "REDonFDTD/EMfunctions.hpp"

/* ELECTROMAGNETIC EFFECTS */

void REDonFDTD::halfTimeStep(source *p, Mesh *g){
  g->time += g->timeStep/2;
  p->timeAdvanceValues(g);
}
