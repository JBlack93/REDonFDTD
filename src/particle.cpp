#include <array>
#include <algorithm>

#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/mesh.hpp"


REDonFDTD::Particle::Particle(Mesh * g){
  prevPos[0] = (double) (g->sizeX-1)/2;
  prevPos[1] = (double) (g->sizeY/2)-0.5;
  prevPos[2] = (double) (g->sizeZ/2)-0.5;
  prevVel[0], prevVel[1], prevVel[2] = 0;
  prevAcc[0], prevAcc[1], prevAcc[2] = 0;

  position[0] = (double) (g->sizeX-1)/2-0.05;
  position[1] = (double) g->sizeY/2-0.05;
  position[2] = (double) g->sizeZ/2-0.05;
  velocity[0] = 0;
  velocity[1] = 0.999*(g->c);
  velocity[2] = 0;
  acceleration[0], acceleration[1], acceleration[2] = 0;

  futPos[0], futPos[1], futPos[2] = 0;
  futVel[0], futVel[1], futVel[2] = 0;
  futAcc[0], futAcc[1], futAcc[2] = 0;

  findCell();

  mass = 1.67262178*pow(10,-27);
  charge = 1.6*pow(10,-19);
  prevGamma = 1;
  gamma = 1;
  futGamma = 1;
}

void REDonFDTD::Particle::findCell(){
  coordinates[0] = floor(position[0]);    // These are the lower values
  coordinates[1] = floor(position[1]);    // of the coordinates in the cell
  coordinates[2] = floor(position[2]);    // which the particle resides in
  coordinates[3] = ceil(position[0]);     // These are the higher values
  coordinates[4] = ceil(position[1]);     // of the coordinates in the cell
  coordinates[5] = ceil(position[2]);     // which the particle resides in
}

std::array<double,3> REDonFDTD::Particle::eFieldProduced(Mesh *g, double x, double y, double z){
  const std::array<double,3> gToSource{x-position[0], y-position[1], z-position[2]};

  const double gToSourceMag = util::magnitude(gToSource);  //STILL NEED TO MAKE THIS EVALUATED AT RETARDED
  const std::array<double,3> dirU{(g->c)*gToSource[0]/(gToSourceMag) - velocity[0],
                           (g->c)*gToSource[1]/(gToSourceMag) - velocity[1],
                           (g->c)*gToSource[2]/(gToSourceMag) - velocity[2]};

  const double dotgToSourceU = util::dot(gToSource, dirU);

  const double prefactor = (charge)/(4*M_PI*(g->epsilon_0));
  const double secFactor = gToSourceMag/(pow(dotgToSourceU/gToSourceMag,3));
  const double firstFactor = ((g->c)*(g->c)-util::dot(velocity,velocity));
  const std::array<double,3> firstTerm{firstFactor*dirU[0], firstFactor*dirU[1], firstFactor*dirU[2]};
  std::array<double,3> secTerm = util::cross(gToSource, util::cross(dirU, acceleration));
  std::for_each(secTerm.begin(),secTerm.end(),
                [&gToSourceMag](double & element){element/=gToSourceMag;});
  const std::array<double,3> eField{prefactor*secFactor*(firstTerm[0]+secTerm[0]),
                             prefactor*secFactor*(firstTerm[1]+secTerm[1]),
                             prefactor*secFactor*(firstTerm[2]+secTerm[2])};
  return eField;
}

std::array<double,3> REDonFDTD::Particle::bFieldProduced(Mesh *g, std::array<double,3> eField,
                                             double x, double y, double z){
  const std::array<double,3> gTosource{x - position[0], y - position[1], z - position[2]};
  const double gTosourceMag = util::magnitude(gTosource);
  const double factor = (1/((g->c)*gTosourceMag));
  std::array<double,3> bField = util::cross(gTosource, eField);
  std::for_each(bField.begin(),bField.end(),[&factor](double & element){element*=factor;});
  return bField;
}

void REDonFDTD::Particle::sourceFunction(Mesh *g){
  findCell();
  for (unsigned i=0; i<2; ++i){
    for (unsigned n=0; n<2; ++n){
      for (unsigned m=0; m<2; ++m){

        const int a = 3*i;       // Simply labels of the coordinate array which
        const int b = 1+3*n;     // correspond to appropriate coordinates such
        const int c = 2+3*m;     // that calculations can be done at all 8 points

        std::array<double,3> eField = eFieldProduced(g, coordinates[a], coordinates[b], coordinates[c]);
        std::array<double,3> bField = bFieldProduced(g, eField, coordinates[a], coordinates[b], coordinates[c]);

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

void REDonFDTD::Particle::newPositionTaylor(Mesh *g){
  futPos[0] = position[0] + (velocity[0])*(g->timeStep) +
    pow(g->timeStep,2)*(acceleration[0])/2;
  futPos[1] = position[1] + (velocity[1])*(g->timeStep) +
    pow(g->timeStep,2)*(acceleration[1])/2;
  futPos[2] = position[2] + (velocity[2])*(g->timeStep) +
    pow(g->timeStep,2)*(acceleration[2])/2;
}

void REDonFDTD::Particle::newVelocityTaylor(Mesh *g){
  futVel[0] = velocity[0] + (g->timeStep)*(acceleration[0]);
  futVel[1] = velocity[1] + (g->timeStep)*(acceleration[1]);
  futVel[2] = velocity[2] + (g->timeStep)*(acceleration[2]);
  futGamma = 1/(sqrt(1-pow(sqrt(pow(futVel[0],2)+
                                      pow(futVel[1],2)+
                                      pow(futVel[2],2))/(g->c),2)));
}

void REDonFDTD::Particle::findAcceleration(std::array<double,3> force){
  futAcc[0] = force[0]/((mass)*(futGamma));
  futAcc[1] = force[1]/((mass)*(futGamma));
  futAcc[2] = force[2]/((mass)*(futGamma));
}

double REDonFDTD::Particle::findGamma(Mesh * g){
  const double velMag = util::magnitude(velocity);
  const double gamma = 1/(sqrt(1-pow(velMag/(g->c),2)));
  return gamma;
}

std::array<double,3> REDonFDTD::Particle::lorentzForce(Mesh *g){
  std::array<double,3> bField;

  bField[0] = g->hx[(((int) futPos[0])*(g->sizeY-1)+((int) futPos[1]))*(g->sizeZ-1)+((int) futPos[2])]+5;
  bField[1] = g->hy[(((int) futPos[0])*(g->sizeY)+((int) futPos[1]))*(g->sizeZ-1)+((int) futPos[2])];
  bField[2] = g->hz[(((int) futPos[0])*(g->sizeY-1)+((int) futPos[1]))*(g->sizeZ)+((int) futPos[2])];

  std::array<double,3> crossProduct = util::cross(futVel, bField);
  std::for_each(crossProduct.begin(), crossProduct.end(),
                [this,&g](double & a){a*=(this->charge)*(g->Mu_0);});
  return crossProduct;
}

double REDonFDTD::Particle::powerRadiated(Mesh * g){

  const double coefficient = (g->Mu_0*pow(charge,2)*pow((futGamma),6))/(6*M_PI*(g->c));
  const std::array<double,3> crossProd = util::cross(futVel,futAcc);
  const double crossProdMag = util::magnitude(crossProd);
  const double magTerm = pow(crossProdMag/(g->c),2);
  const double accSquared = util::dot(futAcc, futAcc);
  return coefficient*(accSquared - magTerm);
}

void REDonFDTD::Particle::velocityAfterRad(Mesh *g, double powerRad){

  const double velMag = util::magnitude(futVel);
  const double iniEnergy = (mass)*pow((g->c),2)*(futGamma);
  const double finalEnergy = iniEnergy - powerRad;//*TimeStep;
  const double finalVelMag = g->c*(sqrt(1-pow(((mass*pow((g->c),2))/finalEnergy),2)));

  std::for_each(futVel.begin(), futVel.end(),
                [&velMag,&finalVelMag](double & vel){vel*=finalVelMag/velMag;});

  futGamma = 1/(sqrt(1-pow(sqrt(pow(futVel[0],2)+pow(futVel[1],2)+
                                   pow(futVel[2],2))/(g->c),2)));
}

void REDonFDTD::Particle::timeAdvanceValues(){
  prevPos = position;
  position = futPos;
  prevVel = velocity;
  velocity = futVel;
  prevAcc = acceleration;
  acceleration = futAcc;
  prevGamma = gamma;
  gamma = futGamma;
}
