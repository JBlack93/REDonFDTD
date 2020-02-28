/** @file macroSetUp.hpp
 *  @brief macros that permit the Mesh struct to be specified */

#ifndef _MACRO_SETUP_H
#define _MACRO_SETUP_H

#include "include/REDonFDTD/meshInit.hpp"

/* 3D mesh */
#define HxG(g, M, N, P)    g->hx[((M) * (SizeYinMesh(g) - 1) + N) * (SizeZinMesh(g) - 1) + P]
#define ChxhG(g, M, N, P)  g->chxh[((M) * (SizeYinMesh(g) - 1) + N) * (SizeZinMesh(g) - 1) + P]
#define ChxeG(g, M, N, P)  g->chxe[((M) * (SizeYinMesh(g) - 1) + N) * (SizeZinMesh(g) - 1) + P]

#define HyG(g, M, N, P)    g->hy[((M) * SizeYinMesh(g) + N) * (SizeZinMesh(g) - 1) + P]
#define ChyhG(g, M, N, P)  g->chyh[((M) * SizeYinMesh(g) + N) * (SizeZinMesh(g) - 1) + P]
#define ChyeG(g, M, N, P)  g->chye[((M) * SizeYinMesh(g) + N) * (SizeZinMesh(g) - 1) + P]

#define HzG(g, M, N, P)    g->hz[((M) * (SizeYinMesh(g) - 1) + N) * SizeZinMesh(g) + P]
#define ChzhG(g, M, N, P)  g->chzh[((M) * (SizeYinMesh(g) - 1) + N) * SizeZinMesh(g) + P]
#define ChzeG(g, M, N, P)  g->chze[((M) * (SizeYinMesh(g) - 1) + N) * SizeZinMesh(g) + P]

#define ExG(g, M, N, P)    g->ex[((M) * SizeYinMesh(g) + N) * SizeZinMesh(g) + P]
#define CexeG(g, M, N, P)  g->cexe[((M) * SizeYinMesh(g) + N) * SizeZinMesh(g) + P]
#define CexhG(g, M, N, P)  g->cexh[((M) * SizeYinMesh(g) + N) * SizeZinMesh(g) + P]

#define EyG(g, M, N, P)    g->ey[((M) * (SizeYinMesh(g) - 1) + N) * SizeZinMesh(g) + P]
#define CeyeG(g, M, N, P)  g->ceye[((M) * (SizeYinMesh(g) - 1) + N) * SizeZinMesh(g) + P]
#define CeyhG(g, M, N, P)  g->ceyh[((M) * (SizeYinMesh(g) - 1) + N) * SizeZinMesh(g) + P]

#define EzG(g, M, N, P)    g->ez[((M) * SizeYinMesh(g) + N) * (SizeZinMesh(g) - 1) + P]
#define CezeG(g, M, N, P)  g->ceze[((M) * SizeYinMesh(g) + N) * (SizeZinMesh(g) - 1) + P]
#define CezhG(g, M, N, P)  g->cezh[((M) * SizeYinMesh(g) + N) * (SizeZinMesh(g) - 1) + P]

#define SizeXinMesh(g)     g->sizeX
#define SizeYinMesh(g)     g->sizeY
#define SizeZinMesh(g)     g->sizeZ

#define TimeG(g)           g->time
#define TimeStepG(g)       g->timeStep
#define MaxTimeG(g)        g->maxTime
#define CdtdsG(g)          g->cdtds



/* macros that assume the "Mesh" is "g" */
/* 3D mesh */
#define Hx(M, N, P)   HxG(g, M, N, P)
#define Chxh(M, N, P) ChxhG(g, M, N, P)
#define Chxe(M, N, P) ChxeG(g, M, N, P)

#define Hy(M, N, P)   HyG(g, M, N, P)

#define Chyh(M, N, P) ChyhG(g, M, N, P)
#define Chye(M, N, P) ChyeG(g, M, N, P)

#define Hz(M, N, P)   HzG(g, M, N, P)
#define Chzh(M, N, P) ChzhG(g, M, N, P)
#define Chze(M, N, P) ChzeG(g, M, N, P)

#define Ex(M, N, P)   ExG(g, M, N, P)
#define Cexe(M, N, P) CexeG(g, M, N, P)
#define Cexh(M, N, P) CexhG(g, M, N, P)

#define Ey(M, N, P)   EyG(g, M, N, P)
#define Ceye(M, N, P) CeyeG(g, M, N, P)
#define Ceyh(M, N, P) CeyhG(g, M, N, P)

#define Ez(M, N, P)   EzG(g, M, N, P)
#define Ceze(M, N, P) CezeG(g, M, N, P)
#define Cezh(M, N, P) CezhG(g, M, N, P)

#define SizeX      SizeXinMesh(g)
#define SizeY      SizeYinMesh(g)
#define SizeZ      SizeZinMesh(g)

#define Time       TimeG(g)
#define TimeStep   TimeStepG(g)
#define MaxTime    MaxTimeG(g)
#define Cdtds      CdtdsG(g)



//Macros for the particle//
//With particle specified as 'particle'//

#define MassP(p)       p->mass
#define ChargeP(p)     p->charge

//Past Values//
#define xPrevPosP(p)   p->prevPos[0]
#define yPrevPosP(p)   p->prevPos[1]
#define zPrevPosP(p)   p->prevPos[2]

#define xPrevVelP(p)   p->prevVel[0]
#define yPrevVelP(p)   p->prevVel[1]
#define zPrevVelP(p)   p->prevVel[2]

#define xPrevAccP(p)   p->prevAcc[0]
#define yPrevAccP(p)   p->prevAcc[1]
#define zPrevAccP(p)   p->prevAcc[2]

//Current Values//
#define xPositionP(p)   p->position[0]
#define yPositionP(p)   p->position[1]
#define zPositionP(p)   p->position[2]

#define xVelocityP(p)   p->velocity[0]
#define yVelocityP(p)   p->velocity[1]
#define zVelocityP(p)   p->velocity[2]

#define xAccelerationP(p)   p->acceleration[0]
#define yAccelerationP(p)   p->acceleration[1]
#define zAccelerationP(p)   p->acceleration[2]

//Future Values//
#define xFutPosP(p)   p->futPos[0]
#define yFutPosP(p)   p->futPos[1]
#define zFutPosP(p)   p->futPos[2]

#define xFutVelP(p)   p->futVel[0]
#define yFutVelP(p)   p->futVel[1]
#define zFutVelP(p)   p->futVel[2]

#define xFutAccP(p)   p->futAcc[0]
#define yFutAccP(p)   p->futAcc[1]
#define zFutAccP(p)   p->futAcc[2]

//Macros for the particle//
//with particle specified as 'p'//

#define Mass    MassP(p)
#define Charge  ChargeP(p)

//Past Values//
#define xPrevPos    xPrevPosP(p)
#define yPrevPos    yPrevPosP(p)
#define zPrevPos    zPrevPosP(p)

#define xPrevVel    xPrevVelP(p)
#define yPrevVel    yPrevVelP(p)
#define zPrevVel    zPrevVelP(p)

#define xPrevAcc    xPrevAccP(p)
#define yPrevAcc    yPrevAccP(p)
#define zPrevAcc    zPrevAccP(p)



//Current Values//
#define xPosition   xPositionP(p)
#define yPosition   yPositionP(p)
#define zPosition   zPositionP(p)

#define xVelocity   xVelocityP(p)
#define yVelocity   yVelocityP(p)
#define zVelocity   zVelocityP(p)

#define xAcceleration   xAccelerationP(p)
#define yAcceleration   yAccelerationP(p)
#define zAcceleration   zAccelerationP(p)


//Future Values//
#define xFutPos    xFutPosP(p)
#define yFutPos    yFutPosP(p)
#define zFutPos    zFutPosP(p)

#define xFutVel    xFutVelP(p)
#define yFutVel    yFutVelP(p)
#define zFutVel    zFutVelP(p)

#define xFutAcc    xFutAccP(p)
#define yFutAcc    yFutAccP(p)
#define zFutAcc    zFutAccP(p)


//Coordinates //

#define coordP(p,a)      p-> coordinates[a]

#define coord(a)         coordP(p,a)


//Gamma//

#define prevGammaP(p)   p->prevGamma
#define gammaP(p)       p->gamma
#define futGammaP(p)    p->futGamma

#define PrevGamma       prevGammaP(p)
#define Gamma           gammaP(p)
#define FutGamma        futGammaP(p)

#endif
