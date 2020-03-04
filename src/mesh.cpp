/* Mesh Class Implementation file*/

#include <cstdio>
#include "REDonFDTD/mesh.hpp"

REDonFDTD::Mesh::Mesh(int x, int y, int z){
  double imp0 = 377.0;
  int mm, nn, pp;
  this->sizeX = x;                       // size of domain
  this->sizeY = y;
  this->sizeZ = z;
  this->timeStep = 5*pow(10,-10);
  this->maxTime = 100*this->timeStep;           // duration of simulation
  this->cdtds = 1.0 / sqrt(3.0);          // Courant number

  hx.resize(sizeX * (sizeY-1) * (sizeZ-1));
  chxh=hx;
  chxe = hx;

  hy.resize((sizeX-1) * (sizeY) * (sizeZ-1));
  chyh = hy;
  chye = hy;

  hz.resize((sizeX-1) * (sizeY-1) * (sizeZ));
  chzh = hz;
  chze = hz;

  ex.resize((sizeX-1) * (sizeY) * (sizeZ));
  cexh = ex;
  cexe = ex;

  ey.resize((sizeX) * (sizeY-1) * (sizeZ));
  ceyh = ey;
  ceye = ey;

  ez.resize((sizeX) * (sizeY) * (sizeZ-1));
  cezh = ez;
  ceze = ez;

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
void REDonFDTD::Mesh::updateH(){
  int mm, nn, pp;
  for (mm = 0; mm < this->sizeX; ++mm){
    for (nn = 0; nn < this->sizeY - 1; ++nn){
      for (pp = 0; pp < this->sizeZ - 1; ++pp){
        this->hx[(mm*(this->sizeY-1)+nn)*(this->sizeZ-1)+pp] = this->chxh[(mm*(this->sizeY-1)+nn)*(this->sizeZ-1)+pp] * this->hx[(mm*(this->sizeY-1)+nn)*(this->sizeZ-1)+pp] +
          this->chxe[(mm*(this->sizeY-1)+nn)*(this->sizeZ-1)+pp] * ((this->ey[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp+1] - this->ey[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp]) -
                                                           (this->ez[(mm*this->sizeY+nn+1)*(this->sizeZ-1)+pp] - this->ez[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp]));
      }
    }
  }

  for (mm = 0; mm < this->sizeX - 1; ++mm){
    for (nn = 0; nn < this->sizeY; ++nn){
      for (pp = 0; pp < this->sizeZ - 1; ++pp){
        this->hy[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] = this->chyh[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] * this->hy[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] +
          this->chye[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] * ((this->ez[((mm+1)*this->sizeY+nn)*(this->sizeZ-1)+pp] - this->ez[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp]) -
                                                       (this->ex[(mm*this->sizeY+nn)*this->sizeZ+pp+1] - this->ex[(mm*this->sizeY+nn)*this->sizeZ+pp]));
      }
    }
  }
  for (mm = 0; mm < this->sizeX - 1; ++mm){
    for (nn = 0; nn < this->sizeY - 1; ++nn){
      for (pp = 0; pp < this->sizeZ; ++pp){
        this->hz[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] = this->chzh[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] * this->hz[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] +
          this->chze[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] * ((this->ex[(mm*this->sizeY+nn+1)*this->sizeZ+pp] - this->ex[(mm*this->sizeY+nn)*this->sizeZ+pp]) -
                                                       (this->ey[((mm+1)*(this->sizeY-1)+nn)*this->sizeZ+pp] - this->ey[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp]));
      }
    }
  }
  return;
}                   /* end updateH() */


/* update electric field */
void REDonFDTD::Mesh::updateE(){
  int mm, nn, pp;

  for (mm = 0; mm < this->sizeX - 1; ++mm){
    for (nn = 1; nn < this->sizeY - 1; ++nn){
      for (pp = 1; pp < this->sizeZ - 1; ++pp){
        this->ex[(mm*this->sizeY+nn)*this->sizeZ+pp] = this->cexe[(mm*this->sizeY+nn)*this->sizeZ+pp] * this->ex[(mm*this->sizeY+nn)*this->sizeZ+pp] +
          this->cexh[(mm*this->sizeY+nn)*this->sizeZ+pp] * ((this->hz[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] - this->hz[(mm*(this->sizeY-1)+nn-1)*this->sizeZ+pp]) -
                                                   (this->hy[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] - this->hy[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp-1]));
      }
    }
  }

  for (mm = 1; mm < this->sizeX - 1; ++mm){
    for (nn = 0; nn < this->sizeY - 1; ++nn){
      for (pp = 1; pp < this->sizeZ - 1; ++pp){
        this->ey[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] = this->ceye[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] * this->ey[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] +
          this->ceyh[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] * ((this->hx[(mm*(this->sizeY-1)+nn)*(this->sizeZ-1)+pp] - (this->hx[(mm*(this->sizeY-1)+nn)*(this->sizeZ-1)+(pp-1)]) -
                                                        (this->hz[(mm*(this->sizeY-1)+nn)*this->sizeZ+pp] - this->hz[((mm-1)*(this->sizeY-1)+nn)*this->sizeZ+pp])));
      }
    }
  }

  for (mm = 1; mm < this->sizeX - 1; ++mm){
    for (nn = 1; nn < this->sizeY - 1; ++nn){
      for (pp = 0; pp < this->sizeZ - 1; ++pp){
        this->ez[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] = this->ceze[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] * this->ez[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] +
          this->cezh[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] * ((this->hy[(mm*this->sizeY+nn)*(this->sizeZ-1)+pp] - this->hy[((mm-1)*this->sizeY+nn)*(this->sizeZ-1)+pp]) -
                                                       (this->hx[(mm*(this->sizeY-1)+nn)*(this->sizeZ-1)+pp] - this->hx[(mm*(this->sizeY-1)+nn-1)*(this->sizeZ-1)+pp]));
      }
    }
  }

  return;
}        /* end updateE() */
