/* Mesh Class Implementation file*/

#include <cstdio>
#include "REDonFDTD/mesh.hpp"

Mesh::Mesh(){
  double imp0 = 377.0;
  int mm, nn, pp;
  this->sizeX = 51;                       // size of domain
  this->sizeY = 50;
  this->sizeZ = 50;
  this->timeStep = 5*pow(10,-10);
  this->maxTime = 100*this->timeStep;           // duration of simulation
  this->cdtds = 1.0 / sqrt(3.0);          // Courant number

  /* memory allocation */
  this->hx = ALLOC_3D(this->hx,   this->sizeX,     this->sizeY - 1, this->sizeZ - 1);
  this->chxh = ALLOC_3D(this->chxh, this->sizeX,     this->sizeY - 1, this->sizeZ - 1);
  this->chxe = ALLOC_3D(this->chxe, this->sizeX,     this->sizeY - 1, this->sizeZ - 1);
  this->hy = ALLOC_3D(this->hy,   this->sizeX - 1, this->sizeY,     this->sizeZ - 1);
  this->chyh = ALLOC_3D(this->chyh, this->sizeX - 1, this->sizeY,     this->sizeZ - 1);
  this->chye = ALLOC_3D(this->chye, this->sizeX - 1, this->sizeY,     this->sizeZ - 1);
  this->hz = ALLOC_3D(this->hz,   this->sizeX - 1, this->sizeY - 1, this->sizeZ);
  this->chzh = ALLOC_3D(this->chzh, this->sizeX - 1, this->sizeY - 1, this->sizeZ);
  this->chze = ALLOC_3D(this->chze, this->sizeX - 1, this->sizeY - 1, this->sizeZ);


  this->ex = ALLOC_3D(this->ex,   this->sizeX - 1, this->sizeY,     this->sizeZ);
  this->cexe = ALLOC_3D(this->cexe, this->sizeX - 1, this->sizeY,     this->sizeZ);
  this->cexh = ALLOC_3D(this->cexh, this->sizeX - 1, this->sizeY,     this->sizeZ);
  this->ey = ALLOC_3D(this->ey,   this->sizeX,     this->sizeY - 1, this->sizeZ);
  this->ceye = ALLOC_3D(this->ceye, this->sizeX,     this->sizeY - 1, this->sizeZ);
  this->ceyh = ALLOC_3D(this->ceyh, this->sizeX,     this->sizeY - 1, this->sizeZ);
  this->ez = ALLOC_3D(this->ez,   this->sizeX,     this->sizeY,     this->sizeZ - 1);
  this->ceze = ALLOC_3D(this->ceze, this->sizeX,     this->sizeY,     this->sizeZ - 1);
  this->cezh = ALLOC_3D(this->cezh, this->sizeX,     this->sizeY,     this->sizeZ - 1);

  /* set electric-field update coefficients */
  for (mm = 0; mm < this->sizeX - 1; ++mm){
    for (nn = 0; nn < this->sizeY; ++nn){
      for (pp = 0; pp < this->sizeZ; ++pp){
        this->cexe[(mm * (this->sizeY) + nn) * this->sizeZ + pp] = 1.0;
        this->cexh[(mm * (this->sizeY) + nn) * this->sizeZ + pp] = this->cdtds * imp0;
      }
    }
  }

  for (mm = 0; mm < this->sizeX; mm++){
    for (nn = 0; nn < this->sizeY - 1; ++nn){
      for (pp = 0; pp < this->sizeZ; ++pp){
        this->ceye[(mm*(this->sizeY - 1) + nn) * this->sizeZ + pp] = 1.0;
        this->ceyh[(mm*(this->sizeY - 1) + nn) * this->sizeZ + pp] = this->cdtds * imp0;
      }
    }
  }


  for (mm = 0; mm < this->sizeX; ++mm){
    for (nn = 0; nn < this->sizeY; ++nn){
      for (pp = 0; pp < this->sizeZ - 1; ++pp){
        this->ceze[(mm * (this->sizeY) + nn) * (this->sizeZ - 1) + pp] = 1.0;
        this->cezh[(mm * (this->sizeY) + nn) * (this->sizeZ - 1) + pp] = this->cdtds * imp0;
      }
    }
  }

  /* set magnetic-field update coefficients */
  for (mm = 0; mm < this->sizeX; ++mm){
    for (nn = 0; nn < this->sizeY - 1; ++nn){
      for (pp = 0; pp < this->sizeZ - 1; ++pp){
        this->chxh[(mm * (this->sizeY - 1) + nn) * (this->sizeZ - 1) + pp] = 1.0;
        this->chxe[(mm * (this->sizeY - 1) + nn) * (this->sizeZ - 1) + pp] = this->cdtds / imp0;
      }
    }
  }

  for (mm = 0; mm < this->sizeX - 1; ++mm){
    for (nn = 0; nn < this->sizeY; ++nn){
      for (pp = 0; pp < this->sizeZ - 1; ++pp){
        this->chyh[(mm * this->sizeY + nn) * (this->sizeZ - 1) + pp] = 1.0;
        this->chye[(mm * this->sizeY + nn) * (this->sizeZ - 1) + pp] = this->cdtds / imp0;
      }
    }
  }

  for (mm = 0; mm < this->sizeX - 1; ++mm){
    for (nn = 0; nn < this->sizeY - 1; ++nn){
      for (pp = 0; pp < this->sizeZ; ++pp){
        this->chzh[(mm * (this->sizeY - 1) + nn) * this->sizeZ + pp] = 1.0;
        this->chze[(mm * (this->sizeY - 1) + nn) * this->sizeZ + pp] = this->cdtds / imp0;
      }
    }
  }

  return;
}          /* end Mesh() */

/* update magnetic field */
void Mesh::updateH(Mesh *g){
  int mm, nn, pp;
  for (mm = 0; mm < g->sizeX; ++mm){
    for (nn = 0; nn < g->sizeY - 1; ++nn){
      for (pp = 0; pp < g->sizeZ - 1; ++pp){
        g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] = g->chxh[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] * g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] +
          g->chxe[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] * ((g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp+1] - g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp]) -
                                                           (g->ez[(mm*g->sizeY+nn+1)*(g->sizeZ-1)+pp] - g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp]));
      }
    }
  }

  for (mm = 0; mm < g->sizeX - 1; ++mm){
    for (nn = 0; nn < g->sizeY; ++nn){
      for (pp = 0; pp < g->sizeZ - 1; ++pp){
        g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] = g->chyh[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] +
          g->chye[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * ((g->ez[((mm+1)*g->sizeY+nn)*(g->sizeZ-1)+pp] - g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp]) -
                                                       (g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp+1] - g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp]));
      }
    }
  }
  for (mm = 0; mm < g->sizeX - 1; ++mm){
    for (nn = 0; nn < g->sizeY - 1; ++nn){
      for (pp = 0; pp < g->sizeZ; ++pp){
        g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] = g->chzh[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] +
          g->chze[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * ((g->ex[(mm*g->sizeY+nn+1)*g->sizeZ+pp] - g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp]) -
                                                       (g->ey[((mm+1)*(g->sizeY-1)+nn)*g->sizeZ+pp] - g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp]));
      }
    }
  }
  return;
}                   /* end updateH() */


/* update electric field */
void Mesh::updateE(Mesh *g){
  int mm, nn, pp;

  for (mm = 0; mm < g->sizeX - 1; ++mm){
    for (nn = 1; nn < g->sizeY - 1; ++nn){
      for (pp = 1; pp < g->sizeZ - 1; ++pp){
        g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp] = g->cexe[(mm*g->sizeY+nn)*g->sizeZ+pp] * g->ex[(mm*g->sizeY+nn)*g->sizeZ+pp] +
          g->cexh[(mm*g->sizeY+nn)*g->sizeZ+pp] * ((g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] - g->hz[(mm*(g->sizeY-1)+nn-1)*g->sizeZ+pp]) -
                                                   (g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] - g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp-1]));
      }
    }
  }

  for (mm = 1; mm < g->sizeX - 1; ++mm){
    for (nn = 0; nn < g->sizeY - 1; ++nn){
      for (pp = 1; pp < g->sizeZ - 1; ++pp){
        g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] = g->ceye[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] +
          g->ceyh[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] * ((g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] - (g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+(pp-1)]) -
                                                        (g->hz[(mm*(g->sizeY-1)+nn)*g->sizeZ+pp] - g->hz[((mm-1)*(g->sizeY-1)+nn)*g->sizeZ+pp])));
      }
    }
  }

  for (mm = 1; mm < g->sizeX - 1; ++mm){
    for (nn = 1; nn < g->sizeY - 1; ++nn){
      for (pp = 0; pp < g->sizeZ - 1; ++pp){
        g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] = g->ceze[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] +
          g->cezh[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] * ((g->hy[(mm*g->sizeY+nn)*(g->sizeZ-1)+pp] - g->hy[((mm-1)*g->sizeY+nn)*(g->sizeZ-1)+pp]) -
                                                       (g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+pp] - g->hx[(mm*(g->sizeY-1)+nn-1)*(g->sizeZ-1)+pp]));
      }
    }
  }

  return;
}        /* end updateE() */
