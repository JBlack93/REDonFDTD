/* Mesh Class Implementation file*/

#include <cstdio>
#include "REDonFDTD/mesh.hpp"

REDonFDTD::Mesh::Mesh(){
  const double imp0 = 377.0;
  int mm, nn, pp;
  timeStep = 5*pow(10,-10);
  maxTime = 100*timeStep;           // duration of simulation
  cdtds = 1.0 / sqrt(3.0);          // Courant number

  /* set electric-field update coefficients */
  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY; ++nn){
      for (pp = 0; pp < sizeZ; ++pp){
        cexe[(mm * (sizeY) + nn) * sizeZ + pp] = 1.0;
        cexh[(mm * (sizeY) + nn) * sizeZ + pp] = cdtds * imp0;
      }
    }
  }

  for (mm = 0; mm < sizeX; mm++){
    for (nn = 0; nn < sizeY - 1; ++nn){
      for (pp = 0; pp < sizeZ; ++pp){
        ceye[(mm*(sizeY - 1) + nn) * sizeZ + pp] = 1.0;
        ceyh[(mm*(sizeY - 1) + nn) * sizeZ + pp] = cdtds * imp0;
      }
    }
  }


  for (mm = 0; mm < sizeX; ++mm){
    for (nn = 0; nn < sizeY; ++nn){
      for (pp = 0; pp < sizeZ - 1; ++pp){
        ceze[(mm * (sizeY) + nn) * (sizeZ - 1) + pp] = 1.0;
        cezh[(mm * (sizeY) + nn) * (sizeZ - 1) + pp] = cdtds * imp0;
      }
    }
  }

  /* set magnetic-field update coefficients */
  for (mm = 0; mm < sizeX; ++mm){
    for (nn = 0; nn < sizeY - 1; ++nn){
      for (pp = 0; pp < sizeZ - 1; ++pp){
        chxh[(mm * (sizeY - 1) + nn) * (sizeZ - 1) + pp] = 1.0;
        chxe[(mm * (sizeY - 1) + nn) * (sizeZ - 1) + pp] = cdtds / imp0;
      }
    }
  }

  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY; ++nn){
      for (pp = 0; pp < sizeZ - 1; ++pp){
        chyh[(mm * sizeY + nn) * (sizeZ - 1) + pp] = 1.0;
        chye[(mm * sizeY + nn) * (sizeZ - 1) + pp] = cdtds / imp0;
      }
    }
  }

  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY - 1; ++nn){
      for (pp = 0; pp < sizeZ; ++pp){
        chzh[(mm * (sizeY - 1) + nn) * sizeZ + pp] = 1.0;
        chze[(mm * (sizeY - 1) + nn) * sizeZ + pp] = cdtds / imp0;
      }
    }
  }

  return;
}          /* end Mesh() */

/* update magnetic field */
void REDonFDTD::Mesh::updateH(){
  int mm, nn, pp;
  for (mm = 0; mm < sizeX; ++mm){
    for (nn = 0; nn < sizeY - 1; ++nn){
      for (pp = 0; pp < sizeZ - 1; ++pp){
        hx[(mm*(sizeY-1)+nn)*(sizeZ-1)+pp] = chxh[(mm*(sizeY-1)+nn)*(sizeZ-1)+pp] * hx[(mm*(sizeY-1)+nn)*(sizeZ-1)+pp] +
          chxe[(mm*(sizeY-1)+nn)*(sizeZ-1)+pp] * ((ey[(mm*(sizeY-1)+nn)*sizeZ+pp+1] - ey[(mm*(sizeY-1)+nn)*sizeZ+pp]) -
                                                  (ez[(mm*sizeY+nn+1)*(sizeZ-1)+pp] - ez[(mm*sizeY+nn)*(sizeZ-1)+pp]));
      }
    }
  }

  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY; ++nn){
      for (pp = 0; pp < sizeZ - 1; ++pp){
        hy[(mm*sizeY+nn)*(sizeZ-1)+pp] = chyh[(mm*sizeY+nn)*(sizeZ-1)+pp] * hy[(mm*sizeY+nn)*(sizeZ-1)+pp] +
          chye[(mm*sizeY+nn)*(sizeZ-1)+pp] * ((ez[((mm+1)*sizeY+nn)*(sizeZ-1)+pp] - ez[(mm*sizeY+nn)*(sizeZ-1)+pp]) -
                                              (ex[(mm*sizeY+nn)*sizeZ+pp+1] - ex[(mm*sizeY+nn)*sizeZ+pp]));
      }
    }
  }
  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY - 1; ++nn){
      for (pp = 0; pp < sizeZ; ++pp){
        hz[(mm*(sizeY-1)+nn)*sizeZ+pp] = chzh[(mm*(sizeY-1)+nn)*sizeZ+pp] * hz[(mm*(sizeY-1)+nn)*sizeZ+pp] +
          chze[(mm*(sizeY-1)+nn)*sizeZ+pp] * ((ex[(mm*sizeY+nn+1)*sizeZ+pp] - ex[(mm*sizeY+nn)*sizeZ+pp]) -
                                              (ey[((mm+1)*(sizeY-1)+nn)*sizeZ+pp] - ey[(mm*(sizeY-1)+nn)*sizeZ+pp]));
      }
    }
  }
  return;
}                   /* end updateH() */


/* update electric field */
void REDonFDTD::Mesh::updateE(){
  int mm, nn, pp;

  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 1; nn < sizeY - 1; ++nn){
      for (pp = 1; pp < sizeZ - 1; ++pp){
        ex[(mm*sizeY+nn)*sizeZ+pp] = cexe[(mm*sizeY+nn)*sizeZ+pp] * ex[(mm*sizeY+nn)*sizeZ+pp] +
          cexh[(mm*sizeY+nn)*sizeZ+pp] * ((hz[(mm*(sizeY-1)+nn)*sizeZ+pp] - hz[(mm*(sizeY-1)+nn-1)*sizeZ+pp]) -
                                          (hy[(mm*sizeY+nn)*(sizeZ-1)+pp] - hy[(mm*sizeY+nn)*(sizeZ-1)+pp-1]));
      }
    }
  }

  for (mm = 1; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY - 1; ++nn){
      for (pp = 1; pp < sizeZ - 1; ++pp){
        ey[(mm*(sizeY-1)+nn)*sizeZ+pp] = ceye[(mm*(sizeY-1)+nn)*sizeZ+pp] * ey[(mm*(sizeY-1)+nn)*sizeZ+pp] +
          ceyh[(mm*(sizeY-1)+nn)*sizeZ+pp] * ((hx[(mm*(sizeY-1)+nn)*(sizeZ-1)+pp] - (hx[(mm*(sizeY-1)+nn)*(sizeZ-1)+(pp-1)]) -
                                               (hz[(mm*(sizeY-1)+nn)*sizeZ+pp] - hz[((mm-1)*(sizeY-1)+nn)*sizeZ+pp])));
      }
    }
  }

  for (mm = 1; mm < sizeX - 1; ++mm){
    for (nn = 1; nn < sizeY - 1; ++nn){
      for (pp = 0; pp < sizeZ - 1; ++pp){
        ez[(mm*sizeY+nn)*(sizeZ-1)+pp] = ceze[(mm*sizeY+nn)*(sizeZ-1)+pp] * ez[(mm*sizeY+nn)*(sizeZ-1)+pp] +
          cezh[(mm*sizeY+nn)*(sizeZ-1)+pp] * ((hy[(mm*sizeY+nn)*(sizeZ-1)+pp] - hy[((mm-1)*sizeY+nn)*(sizeZ-1)+pp]) -
                                              (hx[(mm*(sizeY-1)+nn)*(sizeZ-1)+pp] - hx[(mm*(sizeY-1)+nn-1)*(sizeZ-1)+pp]));
      }
    }
  }

  return;
}        /* end updateE() */
