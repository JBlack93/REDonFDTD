/** @file particleInit.hpp
 *  @brief Contains the Particle class */
#pragma once
#include "REDonFDTD/meshInit.hpp"
#include "REDonFDTD/prototypes.hpp"

//! @brief Particle struct contains all necessary information for updating the position of the particle.
class Particle
{
public:
  Particle(Mesh * g){
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


  };
  ~Particle() = default;

  double charge,     mass;
  double prevGamma,  gamma,     futGamma;
  double *prevPos,   *prevVel,  *prevAcc;
  double *position,  *velocity, *acceleration;
  double *futPos,    *futVel,   *futAcc;
  int *coordinates;
};


// typedef struct Particle Particle;
