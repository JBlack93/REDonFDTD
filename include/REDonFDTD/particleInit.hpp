/** @file particleInit.hpp
 *  @brief Contains the Particle struct */
#ifndef _PARTICLE_INIT_H
#define _PARTICLE_INIT_H

//! @brief Particle struct contains all necessary information for updating the position of the particle.
struct Particle
{
    double charge,     mass;
    double prevGamma,  gamma,     futGamma;
    double *prevPos,   *prevVel,  *prevAcc;
    double *position,  *velocity, *acceleration;
    double *futPos,    *futVel,   *futAcc;
    int *coordinates;
};


typedef struct Particle Particle;

#endif
