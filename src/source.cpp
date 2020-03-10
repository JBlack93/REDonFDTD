#include <array>
#include <algorithm>

#include "REDonFDTD/source.hpp"
#include "REDonFDTD/mesh.hpp"


REDonFDTD::source::source(Mesh *g){
  findCell(g);
}

void REDonFDTD::source::findCell(Mesh *g){
  coordinates[0] = floor(position[0]/g->dS);    // These are the lower values
  coordinates[1] = floor(position[1]/(g->dS));    // of the coordinates in the cell
  coordinates[2] = floor(position[2]/(g->dS));    // which the particle resides in
  coordinates[3] = ceil(position[0]/(g->dS));     // These are the higher values
  coordinates[4] = ceil(position[1]/(g->dS));     // of the coordinates in the cell
  coordinates[5] = ceil(position[2]/(g->dS));     // which the particle resides in
}

void REDonFDTD::source::sourceFunction(Mesh *g){
  findCell(g);
  for (unsigned i=0; i<2; ++i){
    for (unsigned n=0; n<2; ++n){
      for (unsigned m=0; m<2; ++m){

        const int a = 3*i;       // Simply labels of the coordinate array which
        const int b = 1+3*n;     // correspond to appropriate coordinates such
        const int c = 2+3*m;     // that calculations can be done at all 8 points

        std::array<double,3> eField = this->eFieldProduced(g, coordinates[a], coordinates[b], coordinates[c]);
        std::array<double,3> bField = this->bFieldProduced(g, eField, coordinates[a], coordinates[b], coordinates[c]);

        g->ex[(coordinates[a] * g->sizeY + coordinates[b]) *
              g->sizeZ + coordinates[c]] += eField[0];      // Calculation of the effect which
        g->ey[(coordinates[a] * (g->sizeY - 1) + coordinates[b]) *
              g->sizeZ + coordinates[c]]+= eField[1];      // charged particle has on each of
        g->ez[(coordinates[a] * g->sizeY + coordinates[b]) *
              (g->sizeZ - 1) + coordinates[c]]+= eField[2];      // directions of E-Field

        g->hx[(coordinates[a] * (g->sizeY - 1) + coordinates[b]) *
              (g->sizeZ - 1) + coordinates[c]]+= bField[0]/(g->Mu_0);      // Calculation of the effect which
        g->hy[(coordinates[a] * g->sizeY + coordinates[b]) *
              (g->sizeZ - 1) + coordinates[c]]+= bField[1]/(g->Mu_0);      // charged particle has on each of
        g->hz[(coordinates[a] * (g->sizeY - 1) + coordinates[b]) *
              g->sizeZ + coordinates[c]]  += bField[2]/(g->Mu_0);      // these directions of the H-Field

      }
    }
  }// amplitude of change in field due to source
}
