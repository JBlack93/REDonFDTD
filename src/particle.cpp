#include <array>
#include <algorithm>

#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/memAllocation.hpp"


REDonFDTD::Particle::Particle(Mesh * g){
  this->prevPos = ALLOC_1D(this->prevPos,3);
  this->prevPos[0] = (double) (g->sizeX-1)/2;
  this->prevPos[1] = (double) (g->sizeY/2)-0.5;
  this->prevPos[2] = (double) (g->sizeZ/2)-0.5;
  this->prevVel = ALLOC_1D(this->prevVel,3);
  this->prevVel[0] = 0;
  this->prevVel[1] = 0;
  this->prevVel[2] = 0;
  this->prevAcc = ALLOC_1D(this->prevAcc,3);
  this->prevAcc[0] = 0;
  this->prevAcc[1] = 0;
  this->prevAcc[2] = 0;

  this->position = ALLOC_1D(this->position,3);
  this->position[0] = (double) (g->sizeX-1)/2-0.05;
  this->position[1] = (double) g->sizeY/2-0.05;
  this->position[2] = (double) g->sizeZ/2-0.05;
  this->velocity = ALLOC_1D(this->velocity,3);
  this->velocity[0] = 0;
  this->velocity[1] = 0.999*(g->c);
  this->velocity[2] = 0;
  this->acceleration = ALLOC_1D(this->acceleration,3);
  this->acceleration[0] = 0;
  this->acceleration[1] = 0;
  this->acceleration[2] = 0;

  this->futPos = ALLOC_1D(this->futPos,3);
  this->futPos[0] = 0;
  this->futPos[1] = 0;
  this->futPos[2] = 0;
  this->futVel = ALLOC_1D(this->futVel,3);
  this->futVel[0] = 0;
  this->futVel[1] = 0;
  this->futVel[2] = 0;
  this->futAcc = ALLOC_1D(this->futAcc,3);
  this->futAcc[0] = 0;
  this->futAcc[1] = 0;
  this->futAcc[2] = 0;

  this->coordinates = ALLOC_1D(this->coordinates,6);
  this->coordinates[0] =  floor(this->position[0]);        // Set the array element to the lower x coordinate
  this->coordinates[1] =  floor(this->position[1]);        // Set the array element to the lower y coordinate
  this->coordinates[2] =  floor(this->position[2]);        // Set the array element to the lower z coordinate
  this->coordinates[3] =  ceil(this->position[0]);         // Set the array element to the higher x coordinate
  this->coordinates[4] =  ceil(this->position[1]);         // Set the array element to the higher y coordinate
  this->coordinates[5] =  ceil(this->position[2]);         // Set the array element to the higher z coordinate

  this->mass = 1.67262178*pow(10,-27);
  this->charge = 1.6*pow(10,-19);
  this->prevGamma = 1;
  this->gamma = 1;
  this->futGamma = 1;
}

void REDonFDTD::Particle::findCell(){
  this->coordinates[0] = floor(this->position[0]);    // These are the lower values
  this->coordinates[1] = floor(this->position[1]);    // of the coordinates in the cell
  this->coordinates[2] = floor(this->position[2]);    // which the particle resides in
  this->coordinates[3] = ceil(this->position[0]);     // These are the higher values
  this->coordinates[4] = ceil(this->position[1]);     // of the coordinates in the cell
  this->coordinates[5] = ceil(this->position[2]);     // which the particle resides in
}

std::array<double,3> REDonFDTD::Particle::eFieldProduced(Mesh *g, double x, double y, double z){
  std::array<double,3> gridRadius{x,y,z};
  std::array<double,3> sourceRadius{this->position[0],this->position[1],this->position[2]};
  std::array<double,3> velocity{this->velocity[0],this->velocity[1],this->velocity[2]};
  std::array<double,3> acceleration{this->acceleration[0], this->acceleration[1], this->acceleration[2]};

  std::array<double,3> gridToSource{gridRadius[0]-sourceRadius[0],
                                   gridRadius[1]-sourceRadius[1],
                                   gridRadius[2]-sourceRadius[2]};

  double gridToSourceMag = util::magnitude(gridToSource);                       //STILL NEED TO MAKE THIS EVALUATED AT RETARDED
  std::array<double,3> dirU{(g->c)*gridToSource[0]/(gridToSourceMag) - velocity[0],
                           (g->c)*gridToSource[1]/(gridToSourceMag) - velocity[1],
                           (g->c)*gridToSource[2]/(gridToSourceMag) - velocity[2]};

  double dotGridSourceU = util::dot(gridToSource, dirU);

  double prefactor = (this->charge)/(4*M_PI*(g->epsilon_0));
  double secondFactor = gridToSourceMag/(pow(dotGridSourceU/gridToSourceMag,3));
  double firstTermFactor = (pow((g->c),2)-util::dot(velocity,velocity));
  std::array<double,3> firstTerm{firstTermFactor*dirU[0],
                                firstTermFactor*dirU[1],
                                firstTermFactor*dirU[2]};
  std::array<double,3> secondTerm = util::cross(gridToSource, util::cross(dirU, acceleration));
  std::for_each(secondTerm.begin(),secondTerm.end(),
                [&gridToSourceMag](double & element){element/=gridToSourceMag;});
  std::array<double,3> eField{prefactor*secondFactor*(firstTerm[0]+secondTerm[0]),
                             prefactor*secondFactor*(firstTerm[1]+secondTerm[1]),
                             prefactor*secondFactor*(firstTerm[2]+secondTerm[2])};
  return eField;
}

std::array<double,3> REDonFDTD::Particle::bFieldProduced(Mesh *g, std::array<double,3> eField,
                                             double x, double y, double z){
  std::array<double,3> gridRadius{x,y,z};
  std::array<double,3> sourceRadius{this->position[0],this->position[1],this->position[2]};
  std::array<double,3> gridToSource{gridRadius[0] - sourceRadius[0],
                                   gridRadius[1] - sourceRadius[1],
                                   gridRadius[2] - sourceRadius[2]};
  double gridToSourceMag = util::magnitude(gridToSource);
  double factor = (1/((g->c)*gridToSourceMag));
  std::array<double,3> bField = util::cross(gridToSource, eField);
  std::for_each(bField.begin(),bField.end(),[&factor](double & element){element*=factor;});
  return bField;
}

void REDonFDTD::Particle::sourceFunction(Mesh *g){
  this->findCell();
  for (unsigned i=0; i<2; ++i){
    for (unsigned n=0; n<2; ++n){
      for (unsigned m=0; m<2; ++m){

        int a = 3*i;       // Simply labels of the coordinate array which
        int b = 1+3*n;     // correspond to appropriate coordinates such
        int c = 2+3*m;     // that calculations can be done at all 8 points

        std::array<double,3> eField;
        std::array<double,3> bField;
        eField = eFieldProduced(g, this->coordinates[a], this->coordinates[b], this->coordinates[c]);
        bField = bFieldProduced(g, eField, this->coordinates[a], this->coordinates[b], this->coordinates[c]);
        /*        std::cout <<xPosition<<std::endl;
                  std::cout <<(SizeX-1)/2-0.05<<std::endl;
                  std::cout <<coord(a)<<std::endl;
        */
        g->ex[(this->coordinates[a] * g->sizeY + this->coordinates[b]) *
              g->sizeZ + this->coordinates[c]] += eField[0];      // Calculation of the effect which
        g->ey[(this->coordinates[a] * (g->sizeY - 1) + this->coordinates[b]) *
              g->sizeZ + this->coordinates[c]]+= eField[1];      // charged particle has on each of
        g->ez[(this->coordinates[a] * g->sizeY + this->coordinates[b]) *
              (g->sizeZ - 1) + this->coordinates[c]]+= eField[2];      // directions of E-Field

        g->hx[(this->coordinates[a] * (g->sizeY - 1) + this->coordinates[b]) *
              (g->sizeZ - 1) + this->coordinates[c]]+= bField[0]/(g->Mu_0);      // Calculation of the effect which
        g->hy[(this->coordinates[a] * g->sizeY + this->coordinates[b]) *
              (g->sizeZ - 1) + this->coordinates[c]]+= bField[1]/(g->Mu_0);      // charged particle has on each of
        g->hz[(this->coordinates[a] * (g->sizeY - 1) + this->coordinates[b]) *
              g->sizeZ + this->coordinates[c]]  += bField[2]/(g->Mu_0);      // these directions of the H-Field

      }
    }
  }// amplitude of change in field due to source

}

void REDonFDTD::Particle::newPositionTaylor(Mesh *g)
{
  this->futPos[0] = this->position[0] + (this->velocity[0])*(g->timeStep) +
    pow(g->timeStep,2)*(this->acceleration[0])/2;
  this->futPos[1] = this->position[1] + (this->velocity[1])*(g->timeStep) +
    pow(g->timeStep,2)*(this->acceleration[1])/2;
  this->futPos[2] = this->position[2] + (this->velocity[2])*(g->timeStep) +
    pow(g->timeStep,2)*(this->acceleration[2])/2;
}

void REDonFDTD::Particle::newVelocityTaylor(Mesh *g)
{
  this->futVel[0] = this->velocity[0] + (g->timeStep)*(this->acceleration[0]);
  this->futVel[1] = this->velocity[1] + (g->timeStep)*(this->acceleration[1]);
  this->futVel[2] = this->velocity[2] + (g->timeStep)*(this->acceleration[2]);
  this->futGamma = 1/(sqrt(1-pow(sqrt(pow(this->futVel[0],2)+
                                      pow(this->futVel[1],2)+
                                      pow(this->futVel[2],2))/(g->c),2)));
}

void REDonFDTD::Particle::findAcceleration(std::array<double,3> force){
  this->futAcc[0] = force[0]/((this->mass)*(this->futGamma));
  this->futAcc[1] = force[1]/((this->mass)*(this->futGamma));
  this->futAcc[2] = force[2]/((this->mass)*(this->futGamma));
}

double REDonFDTD::Particle::findGamma(Mesh * g)
{
  std::array<double,3> vel{this->velocity[0],this->velocity[1],this->velocity[2]};
  double velMag = util::magnitude(vel);
  double gamma = 1/(sqrt(1-pow(velMag/(g->c),2)));
  return gamma;
}

std::array<double,3> REDonFDTD::Particle::lorentzForce(Mesh *g){
  std::array<double,3> velocity{this->futVel[0], this->futVel[1], this->futVel[2]};
  std::array<double,3> bField;

  bField[0] = g->hx[(((int) this->futPos[0])*(g->sizeY-1)+((int) this->futPos[1]))*(g->sizeZ-1)+((int) this->futPos[2])]+5;
  bField[1] = g->hy[(((int) this->futPos[0])*(g->sizeY)+((int) this->futPos[1]))*(g->sizeZ-1)+((int) this->futPos[2])];
  bField[2] = g->hz[(((int) this->futPos[0])*(g->sizeY-1)+((int) this->futPos[1]))*(g->sizeZ)+((int) this->futPos[2])];

  std::array<double,3> crossProduct = util::cross(velocity, bField);
  std::for_each(crossProduct.begin(), crossProduct.end(),
                [this,&g](double & a){a*=(this->charge)*(g->Mu_0);});
  return crossProduct;
}

double REDonFDTD::Particle::powerRadiated(Mesh * g){
  std::array<double,3> velocity{this->futVel[0], this->futVel[1], this->futVel[2]};
  std::array<double,3> acceleration{this->futAcc[0], this->futAcc[1], this->futAcc[2]};

  double coefficient = (g->Mu_0*pow(this->charge,2)*pow((this->futGamma),6))/(6*M_PI*(g->c));
  std::array<double,3> crossProd;
  crossProd = util::cross(velocity,acceleration);
  double crossProdMag = util::magnitude(crossProd);
  double magTerm = pow(crossProdMag/(g->c),2);
  double accSquared = util::dot(acceleration, acceleration);
  double powerRad = coefficient*(accSquared - magTerm);
  return powerRad;
}

void REDonFDTD::Particle::velocityAfterRad(Mesh *g, double powerRad){
  std::array<double,3> velocity{this->futVel[0], this->futVel[1], this->futVel[2]};
  std::array<double,3> acceleration{this->futAcc[0], this->futAcc[1], this->futAcc[2]};

  double velMag = util::magnitude(velocity);
  double iniEnergy = (this->mass)*pow((g->c),2)*(this->futGamma);
  double finalEnergy = iniEnergy - powerRad;//*TimeStep;
  double finalVelMag = g->c*(sqrt(1-pow((((this->mass)*pow((g->c),2))/finalEnergy),2)));

  std::for_each(velocity.begin(), velocity.end(),
                [&velMag,&finalVelMag](double & vel){vel*=finalVelMag/velMag;});

  this->futVel[0] = velocity[0];
  this->futVel[1] = velocity[1];
  this->futVel[2] = velocity[2];
  this->futGamma = 1/(sqrt(1-pow(sqrt(pow(this->futVel[0],2)+pow(this->futVel[1],2)+
                                   pow(this->futVel[2],2))/(g->c),2)));
}
