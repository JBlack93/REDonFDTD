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

std::array<double,3> REDonFDTD::source::velocityEField(Mesh *g, double x, double y, double z){
  return eFieldProduced(g,x,y,z);
}

void REDonFDTD::source::InitialiseMesh(Mesh * g){
  std::array<double,3> eField;
  std::array<double,3> bField;
  for (int mm = 0; mm < g->sizeX; ++mm){
    for (int nn = 0; nn < g->sizeY; ++nn){
      for (int pp = 0; pp < g->sizeZ; ++pp){
        eField = velocityEField(g, mm, nn, pp);
        bField = bFieldProduced(g, eField, mm, nn, pp);

        if(mm!=g->sizeX-1)   g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp] = eField[0];
        if(nn!=g->sizeY-1)   g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] = eField[1];
        if(pp!=g->sizeZ-1)   g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] = eField[2];

        if(nn!=g->sizeY-1 &&pp!=g->sizeZ-1)   g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] = bField[0]/(g->Mu_0);
        if(mm!=g->sizeX-1 &&pp!=g->sizeZ-1)   g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp]     = bField[1]/(g->Mu_0);
        if(nn!=g->sizeY-1 &&mm!=g->sizeX-1)   g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp]     = bField[2]/(g->Mu_0);
      }
    }
  }
}

void REDonFDTD::source::sourceFunction(Mesh *g, int analyticRange){
  findCell(g);

  for (int i=coordinates[0]-analyticRange; i<=coordinates[3]+analyticRange; ++i){
    for (int n=coordinates[1]-analyticRange; n<=coordinates[4]+analyticRange; ++n){
      for (int m=coordinates[2]-analyticRange; m<=coordinates[5]+analyticRange; ++m){

        std::array<double,3> eField = this->eFieldProduced(g, i, n, m);
        std::array<double,3> bField = this->bFieldProduced(g, eField, i, n, m);

        g->ex[(i * g->sizeY + n) * g->sizeZ + m]       = eField[0];
        g->ey[(i * (g->sizeY - 1) + n) * g->sizeZ + m] = eField[1];
        g->ez[(i * g->sizeY + n) * (g->sizeZ - 1) + m] = eField[2];

        g->hx[(i * (g->sizeY - 1) + n) * (g->sizeZ - 1) + m] = bField[0]/(g->Mu_0);
        g->hy[(i * g->sizeY + n) * (g->sizeZ - 1) + m]       = bField[1]/(g->Mu_0);
        g->hz[(i * (g->sizeY - 1) + n) * g->sizeZ + m]       = bField[2]/(g->Mu_0);
      }
    }
  }// amplitude of change in field due to source

}
