#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "REDonFDTD/prototypes.hpp"
#include "REDonFDTD/particleInit.hpp"
#include "REDonFDTD/memAllocation.hpp"


/* Calculate the 6 points on the axes which produce
 * the 8 grid points closest to the point charge.
 */
void findCell(Particle *p)
{
    p->coordinates[0] = floor(p->position[0]);    // These are the lower values
    p->coordinates[1] = floor(p->position[1]);    // of the coordinates in the cell
    p->coordinates[2] = floor(p->position[2]);    // which the particle resides in
    p->coordinates[3] = ceil(p->position[0]);     // These are the higher values
    p->coordinates[4] = ceil(p->position[1]);     // of the coordinates in the cell
    p->coordinates[5] = ceil(p->position[2]);     // which the particle resides in
}

/* Changes the the electric and magnetic field at 8 difference points based on
 * point paths movement through the mesh. Most key function in entire operation
 */
void sourceFunction(Particle *p, Mesh *g)
{
    findCell(p);
    for (unsigned i=0; i<2; ++i)
    {
        for (unsigned n=0; n<2; ++n)
        {
            for (unsigned m=0; m<2; ++m)
            {

            int a = 3*i;       // Simply labels of the coordinate array which
            int b = 1+3*n;     // correspond to appropriate coordinates such
            int c = 2+3*m;     // that calculations can be done at all 8 points

            std::vector<double> eField(3);
            std::vector<double> bField(3);
            eField = eFieldProduced(p, g, p->coordinates[a], p->coordinates[b], p->coordinates[c]);
            bField = bFieldProduced(p, g, eField, p->coordinates[a], p->coordinates[b], p->coordinates[c]);
  /*        std::cout <<xPosition<<std::endl;
            std::cout <<(SizeX-1)/2-0.05<<std::endl;
            std::cout <<coord(a)<<std::endl;
  */
            g->ex[(p->coordinates[a] * g->sizeY + p->coordinates[b]) *
                  g->sizeZ + p->coordinates[c]] += eField[0];      // Calculation of the effect which
            g->ey[(p->coordinates[a] * (g->sizeY - 1) + p->coordinates[b]) *
                  g->sizeZ + p->coordinates[c]]+= eField[1];      // charged particle has on each of
            g->ez[(p->coordinates[a] * g->sizeY + p->coordinates[b]) *
                  (g->sizeZ - 1) + p->coordinates[c]]+= eField[2];      // directions of E-Field

            g->hx[(p->coordinates[a] * (g->sizeY - 1) + p->coordinates[b]) *
                  (g->sizeZ - 1) + p->coordinates[c]]+= bField[0]/(g->Mu_0);      // Calculation of the effect which
            g->hy[(p->coordinates[a] * g->sizeY + p->coordinates[b]) *
                  (g->sizeZ - 1) + p->coordinates[c]]+= bField[1]/(g->Mu_0);      // charged particle has on each of
            g->hz[(p->coordinates[a] * (g->sizeY - 1) + p->coordinates[b]) *
                  g->sizeZ + p->coordinates[c]]  += bField[2]/(g->Mu_0);      // these directions of the H-Field

            }
        }
    }// amplitude of change in field due to source
}

std::vector<double> eFieldProduced(Particle *p, Mesh *g, double x, double y, double z)
{
  std::vector<double> gridRadius{x,y,z};
  std::vector<double> sourceRadius{p->position[0],p->position[1],p->position[2]};
  std::vector<double> velocity{p->velocity[0],p->velocity[1],p->velocity[2]};
  std::vector<double> acceleration{p->acceleration[0], p->acceleration[1], p->acceleration[2]};

  std::vector<double> gridToSource{gridRadius[0]-sourceRadius[0],
                                   gridRadius[1]-sourceRadius[1],
                                   gridRadius[2]-sourceRadius[2]};

  double gridToSourceMag = magnitude(gridToSource);                       //STILL NEED TO MAKE THIS EVALUATED AT RETARDED
  std::vector<double> dirU{(g->c)*gridToSource[0]/(gridToSourceMag) - velocity[0],
                           (g->c)*gridToSource[1]/(gridToSourceMag) - velocity[1],
                           (g->c)*gridToSource[2]/(gridToSourceMag) - velocity[2]};

  double dotGridSourceU = dot(gridToSource, dirU);

  double prefactor = (p->charge)/(4*M_PI*(g->epsilon_0));
  double secondFactor = gridToSourceMag/(pow(dotGridSourceU/gridToSourceMag,3));
  double firstTermFactor = (pow((g->c),2)-dot(velocity,velocity));
  std::vector<double> firstTerm{firstTermFactor*dirU[0],
                                firstTermFactor*dirU[1],
                                firstTermFactor*dirU[2]};
  std::vector<double> secondTerm = cross(gridToSource, cross(dirU, acceleration));
  std::for_each(secondTerm.begin(),secondTerm.end(),
                [&gridToSourceMag](double & element){element/=gridToSourceMag;});
  std::vector<double> eField{prefactor*secondFactor*(firstTerm[0]+secondTerm[0]),
                             prefactor*secondFactor*(firstTerm[1]+secondTerm[1]),
                             prefactor*secondFactor*(firstTerm[2]+secondTerm[2])};
  return eField;
}


std::vector<double> bFieldProduced(Particle *p, Mesh *g, std::vector<double> eField,
                                   double x, double y, double z)
{
  std::vector<double> gridRadius{x,y,z};
  std::vector<double> sourceRadius{p->position[0],p->position[1],p->position[2]};
  std::vector<double> gridToSource{gridRadius[0] - sourceRadius[0],
                                   gridRadius[1] - sourceRadius[1],
                                   gridRadius[2] - sourceRadius[2]};
  double gridToSourceMag = magnitude(gridToSource);
  double factor = (1/((g->c)*gridToSourceMag));
  std::vector<double> bField = cross(gridToSource, eField);
  std::for_each(bField.begin(),bField.end(),[&factor](double & element){element*=factor;});
  return bField;
}
