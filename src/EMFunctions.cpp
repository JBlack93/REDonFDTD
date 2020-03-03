/* This Header File contains all the functions which call for global values
 * which therefore includes all the Electromagnetic effects
 */

#include <cmath>
#include "REDonFDTD/EMfunctions.hpp"
#include "REDonFDTD/particleInit.hpp"
#include "REDonFDTD/meshInit.hpp"


/* ELECTROMAGNETIC EFFECTS */

std::vector<double> lorentzForce(Particle *p, Mesh *g)
{
  std::vector<double> velocity{p->futVel[0], p->futVel[1], p->futVel[2]};
  std::vector<double> bField(3);

  bField[0] = g->hx[(((int) p->futPos[0])*(g->sizeY-1)+((int) p->futPos[1]))*(g->sizeZ-1)+((int) p->futPos[2])]+5;
  bField[1] = g->hy[(((int) p->futPos[0])*(g->sizeY)+((int) p->futPos[1]))*(g->sizeZ-1)+((int) p->futPos[2])];
  bField[2] = g->hz[(((int) p->futPos[0])*(g->sizeY-1)+((int) p->futPos[1]))*(g->sizeZ)+((int) p->futPos[2])];

  std::vector<double> crossProduct = manip::cross(velocity, bField);
  std::for_each(crossProduct.begin(), crossProduct.end(),
                [& p, &g](double & a){a*=(p->charge)*(g->Mu_0);});
  return crossProduct;
}

double powerRadiated(Particle *p, Mesh * g)
{
  std::vector<double> velocity{p->futVel[0], p->futVel[1], p->futVel[2]};
  std::vector<double> acceleration{p->futAcc[0], p->futAcc[1], p->futAcc[2]};

  double coefficient = (g->Mu_0*pow(p->charge,2)*pow((p->futGamma),6))/(6*M_PI*(g->c));
  std::vector<double> crossProd(3);
  crossProd = manip::cross(velocity,acceleration);
  double crossProdMag = manip::magnitude(crossProd);
  double magTerm = pow(crossProdMag/(g->c),2);
  double accSquared = manip::dot(acceleration, acceleration);
  double powerRad = coefficient*(accSquared - magTerm);
  return powerRad;
}

void velocityAfterRad(Particle *p, Mesh *g, double powerRad)
{
  std::vector<double> velocity{p->futVel[0], p->futVel[1], p->futVel[2]};
  std::vector<double> acceleration{p->futAcc[0], p->futAcc[1], p->futAcc[2]};

  double velMag = manip::magnitude(velocity);
  double iniEnergy = (p->mass)*pow((g->c),2)*(p->futGamma);
  double finalEnergy = iniEnergy - powerRad;//*TimeStep;
  double finalVelMag = g->c*(sqrt(1-pow((((p->mass)*pow((g->c),2))/finalEnergy),2)));

  std::for_each(velocity.begin(), velocity.end(),
                [&velMag,&finalVelMag](double & vel){vel*=finalVelMag/velMag;});

  p->futVel[0] = velocity[0];
  p->futVel[1] = velocity[1];
  p->futVel[2] = velocity[2];
  p->futGamma = 1/(sqrt(1-pow(sqrt(pow(p->futVel[0],2)+pow(p->futVel[1],2)+
                                   pow(p->futVel[2],2))/(g->c),2)));
}


void timeAdvanceValues(Particle *p)
{
    p->prevPos[0]  = p->position[0];
    p->prevPos[1]  = p->position[1];
    p->prevPos[2]  = p->position[2];

    p->position[0] = p->futPos[0];
    p->position[1] = p->futPos[1];
    p->position[2] = p->futPos[2];

    p->prevVel[0]  = p->velocity[0];
    p->prevVel[1]  = p->velocity[1];
    p->prevVel[2]  = p->velocity[2];

    p->velocity[0] = p->futVel[0];
    p->velocity[1] = p->futVel[1];
    p->velocity[2] = p->futVel[2];

    p->prevAcc[0] = p->acceleration[0];
    p->prevAcc[1] = p->acceleration[1];
    p->prevAcc[2] = p->acceleration[2];

    p->acceleration[0] = p->futAcc[0];
    p->acceleration[1] = p->futAcc[1];
    p->acceleration[2] = p->futAcc[2];

    p->prevGamma = p->gamma;
    p->gamma = p->futGamma;
}

void halfTimeStep(Particle *p, Mesh *g)
{
    g->time += g->timeStep/2;
    p->newPositionTaylor(g);
    p->newVelocityTaylor(g);
    std::vector<double> force = lorentzForce(p, g);
    p->findAcceleration(force);
    double powerRad = powerRadiated(p, g);
    if (powerRad !=0)   velocityAfterRad(p, g, powerRad);
    timeAdvanceValues(p);
}
