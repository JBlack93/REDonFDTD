#include <array>
#include <algorithm>

#include "REDonFDTD/source.hpp"
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/ricker.hpp"

REDonFDTD::source::source(Mesh *g){
  findCell(g);
}

REDonFDTD::source * REDonFDTD::source::Create(Mesh *g, config configuration, sourceType Type){
    if (Type == src_Particle)   return new REDonFDTD::Particle(g, configuration);
    if (Type == src_ricker)     return new REDonFDTD::ricker(g, configuration);
    else return NULL;
}

void REDonFDTD::source::findCell(Mesh *g){
  coordinates[0] = floor(position[0]/g->dS);    // These are the lower values
  coordinates[1] = floor(position[1]/(g->dS));    // of the coordinates in the cell
  coordinates[2] = floor(position[2]/(g->dS));    // which the particle resides in
  coordinates[3] = ceil(position[0]/(g->dS));     // These are the higher values
  coordinates[4] = ceil(position[1]/(g->dS));     // of the coordinates in the cell
  coordinates[5] = ceil(position[2]/(g->dS));     // which the particle resides in
}

void REDonFDTD::source::sourceFunction(Mesh *g, int analyticRange){
  findCell(g);

  for (int i=coordinates[0]-analyticRange; i<=coordinates[3]+analyticRange; ++i){
    for (int n=coordinates[1]-analyticRange; n<=coordinates[4]+analyticRange; ++n){
      for (int m=coordinates[2]-analyticRange; m<=coordinates[5]+analyticRange; ++m){

        std::array<double,3> eField = this->eFieldProduced(g, i, n, m);
        std::array<double,3> bField = this->bFieldProduced(g, eField, i, n, m);

        g->ex[(i * g->sizeY + n) * g->sizeZ + m] += eField[0];
        g->ey[(i * (g->sizeY - 1) + n) * g->sizeZ + m]+= eField[1];
        g->ez[(i * g->sizeY + n) * (g->sizeZ - 1) + m]+= eField[2];

        g->hx[(i * (g->sizeY - 1) + n) * (g->sizeZ - 1) + m]+= bField[0]/(g->Mu_0);
        g->hy[(i * g->sizeY + n) * (g->sizeZ - 1) + m]+= bField[1]/(g->Mu_0);
        g->hz[(i * (g->sizeY - 1) + n) * g->sizeZ + m]  += bField[2]/(g->Mu_0);
      }
    }
  }// amplitude of change in field due to source

}
