#ifndef _PARTICLE_INIT_H
#define _PARTICLE_INIT_H


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
