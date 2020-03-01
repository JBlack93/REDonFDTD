/** @file macroSetUp.hpp
 *  @brief macros that permit the Mesh struct to be specified */
#pragma once

#include "REDonFDTD/meshInit.hpp"

/* 3D mesh */
#define HxG(g, M, N, P)    g->hx[((M) * (g->sizeY - 1) + N) * (g->sizeZ - 1) + P]
#define ChxhG(g, M, N, P)  g->chxh[((M) * (g->sizeY - 1) + N) * (g->sizeZ - 1) + P]
#define ChxeG(g, M, N, P)  g->chxe[((M) * (g->sizeY - 1) + N) * (g->sizeZ - 1) + P]

#define HyG(g, M, N, P)    g->hy[((M) * g->sizeY + N) * (g->sizeZ - 1) + P]
#define ChyhG(g, M, N, P)  g->chyh[((M) * g->sizeY + N) * (g->sizeZ - 1) + P]
#define ChyeG(g, M, N, P)  g->chye[((M) * g->sizeY + N) * (g->sizeZ - 1) + P]

#define HzG(g, M, N, P)    g->hz[((M) * (g->sizeY - 1) + N) * g->sizeZ + P]
#define ChzhG(g, M, N, P)  g->chzh[((M) * (g->sizeY - 1) + N) * g->sizeZ + P]
#define ChzeG(g, M, N, P)  g->chze[((M) * (g->sizeY - 1) + N) * g->sizeZ + P]

#define ExG(g, M, N, P)    g->ex[((M) * g->sizeY + N) * g->sizeZ + P]
#define CexeG(g, M, N, P)  g->cexe[((M) * g->sizeY + N) * g->sizeZ + P]
#define CexhG(g, M, N, P)  g->cexh[((M) * g->sizeY + N) * g->sizeZ + P]

#define EyG(g, M, N, P)    g->ey[((M) * (g->sizeY - 1) + N) * g->sizeZ + P]
#define CeyeG(g, M, N, P)  g->ceye[((M) * (g->sizeY - 1) + N) * g->sizeZ + P]
#define CeyhG(g, M, N, P)  g->ceyh[((M) * (g->sizeY - 1) + N) * g->sizeZ + P]

#define EzG(g, M, N, P)    g->ez[((M) * g->sizeY + N) * (g->sizeZ - 1) + P]
#define CezeG(g, M, N, P)  g->ceze[((M) * g->sizeY + N) * (g->sizeZ - 1) + P]
#define CezhG(g, M, N, P)  g->cezh[((M) * g->sizeY + N) * (g->sizeZ - 1) + P]

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
