/* Mesh Class Implementation file*/

#include <filesystem>
#include <cstdio>
#include "REDonFDTD/mesh.hpp"

REDonFDTD::Mesh::Mesh(){
  std::filesystem::remove_all( "output" );
  std::filesystem::create_directory("output");
  abccoef = (cdtds - 1.0) / (cdtds + 1.0);
  return;
}

REDonFDTD::Mesh::Mesh(config meshConfig): REDonFDTD::Mesh::Mesh(){
  sizeX = meshConfig.sizeX;
  sizeY = meshConfig.sizeY;
  sizeZ = meshConfig.sizeZ;
  steps = meshConfig.steps;
  timeStep = meshConfig.timeStep;
  dS = c*timeStep;
  maxTime = steps*timeStep;

  hx.resize(sizeX*(sizeY-1)*(sizeZ-1), 0);
  chxh.resize(sizeX*(sizeY-1)*(sizeZ-1), 1.0);
  chxe.resize(sizeX*(sizeY-1)*(sizeZ-1), cdtds/377.0);

  hy.resize(sizeZ*(sizeY-1)*(sizeX-1),0);
  chyh.resize(sizeZ*(sizeY-1)*(sizeX-1),1.0);
  chye.resize(sizeZ*(sizeY-1)*(sizeX-1), cdtds/377.0);

  hz.resize(sizeY*(sizeZ-1)*(sizeX-1),0);
  chzh.resize(sizeY*(sizeZ-1)*(sizeX-1),1.0);
  chze.resize(sizeY*(sizeZ-1)*(sizeX-1), cdtds/377.0);

  ex.resize(sizeZ*(sizeY)*(sizeX-1),0);
  cexh.resize(sizeZ*(sizeY)*(sizeX-1), cdtds*377.0);
  cexe.resize(sizeZ*(sizeY)*(sizeX-1),1.0);

  ey.resize(sizeZ*(sizeY-1)*(sizeX),0);
  ceyh.resize(sizeZ*(sizeY-1)*(sizeX), cdtds*377.0);
  ceye.resize(sizeZ*(sizeY-1)*(sizeX),1.0);

  ez.resize(sizeY*(sizeZ-1)*(sizeX),0);
  cezh.resize(sizeY*(sizeZ-1)*(sizeX), cdtds*377.0);
  ceze.resize(sizeY*(sizeZ-1)*(sizeX),1.0);

  eyx0.resize((sizeY-1)*sizeZ);
  ezx0.resize(sizeY*(sizeZ-1));
  eyx1.resize((sizeY-1)*sizeZ);
  ezx1.resize(sizeY*(sizeZ-1));

  exy0.resize((sizeX-1)*sizeZ);
  ezy0.resize(sizeX*(sizeZ-1));
  exy1.resize((sizeX-1)*sizeZ);
  ezy1.resize(sizeX*(sizeZ-1));

  exz0.resize((sizeX-1)*sizeY);
  eyz0.resize(sizeX*(sizeY-1));
  exz1.resize((sizeX-1)*sizeY);
  eyz1.resize(sizeX*(sizeY-1));
}

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

/* function that applies ABC -- called once per time step */
void REDonFDTD::Mesh::updateABC()
{
  int mm, nn, pp;
  /* ABC at "x0" */
  mm = 0;
  for (nn = 0; nn < sizeY - 1; ++nn){
    for (pp = 0; pp < sizeZ; ++pp){
      ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp] =
        eyx0[nn*(sizeZ)+pp] + abccoef *
        (ey[((mm+1) * (sizeY - 1) + nn) * sizeZ + pp] -
         ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp]);

      eyx0[nn*(sizeZ)+pp] = ey[((mm+1) * (sizeY - 1) + nn) * sizeZ + pp];
    }
  }
  for (nn = 0; nn < sizeY; ++nn){
    for (pp = 0; pp < sizeZ - 1; ++pp){
      ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp] = ezx0[nn*(sizeZ-1)+pp] + abccoef *
        (ez[((mm+1)*(sizeY)+nn)*(sizeZ-1)+pp] - ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp]);
      ezx0[nn*(sizeZ-1)+pp] = ez[((mm+1)*(sizeY)+nn)*(sizeZ-1)+pp];
    }
  }

  /* ABC at "x1" */
  mm = sizeX - 1;

  for (nn = 0; nn < sizeY - 1; ++nn){
    for (pp = 0; pp < sizeZ; ++pp){
      ey[(mm*(sizeY-1)+nn)*(sizeZ)+pp] = eyx1[nn*(sizeZ)+pp] + abccoef *
        (ey[((mm-1)*(sizeY-1)+nn)*(sizeZ)+pp] - ey[(mm*(sizeY-1)+nn)*(sizeZ)+pp]);
      eyx1[nn*(sizeZ)+pp] = ey[((mm-1)*(sizeY-1)+nn)*(sizeZ)+pp];
    }
  }
  for (nn = 0; nn < sizeY; ++nn){
    for (pp = 0; pp < sizeZ - 1; ++pp){
      ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp] = ezx1[nn*(sizeZ-1)+pp] + abccoef *
        (ez[((mm-1)*(sizeY)+nn)*(sizeZ-1)+pp] - ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp]);
      ezx1[nn*(sizeZ-1)+pp] = ez[((mm-1)*(sizeY)+nn)*(sizeZ-1)+pp];
    }
  }

  /* ABC at "y0" */
  nn = 0;
  for (mm = 0; mm < sizeX - 1; ++mm){
    for (pp = 0; pp < sizeZ; ++pp){
      ex[(mm*(sizeY)+nn)*(sizeZ)+pp] = exy0[mm*(sizeZ)+pp] + abccoef *
        (ex[(mm*(sizeY)+nn+1)*(sizeZ)+pp] - ex[(mm*(sizeY)+nn)*(sizeZ)+pp]);
      exy0[mm*(sizeZ)+pp] = ex[(mm*(sizeY)+nn+1)*(sizeZ)+pp];
    }
  }

  for (mm = 0; mm < sizeX; ++mm){
    for (pp = 0; pp < sizeZ - 1; ++pp){
      ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp] = ezy0[mm*(sizeZ-1)+pp] + abccoef *
        (ez[(mm*(sizeY)+nn+1)*(sizeZ-1)+pp] - ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp]);
      ezy0[mm*(sizeZ-1)+pp] = ez[(mm*(sizeY)+nn+1)*(sizeZ-1)+pp];
    }
  }


  /* ABC at "y1" */
  nn = sizeY - 1;
  for (mm = 0; mm < sizeX - 1; ++mm){
    for (pp = 0; pp < sizeZ; ++pp){
      ex[(mm*(sizeY)+nn)*(sizeZ)+pp] = exy1[mm*(sizeZ)+pp] + abccoef *
        (ex[(mm*(sizeY)+nn-1)*(sizeZ)+pp] - ex[(mm*(sizeY)+nn)*(sizeZ)+pp]);
      exy1[mm*(sizeZ)+pp] = ex[(mm*(sizeY)+nn-1)*(sizeZ)+pp];
    }
  }
  for (mm = 0; mm < sizeX; ++mm){
    for (pp = 0; pp < sizeZ - 1; ++pp){
      ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp] = ezy1[mm*(sizeZ-1)+pp] + abccoef *
        (ez[(mm*(sizeY)+nn-1)*(sizeZ-1)+pp] - ez[(mm*(sizeY)+nn)*(sizeZ-1)+pp]);
      ezy1[mm*(sizeZ-1)+pp] = ez[(mm*(sizeY)+nn-1)*(sizeZ-1)+pp];
    }
  }

  /* ABC at "z0" (bottom) */
  pp = 0;
  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY; ++nn){
      ex[(mm*(sizeY)+nn)*(sizeZ)+pp] = exz0[mm*(sizeY)+nn] + abccoef *
        (ex[(mm*(sizeY)+nn)*(sizeZ)+pp+1] - ex[(mm*(sizeY)+nn)*(sizeZ)+pp]);
      exz0[mm*(sizeY)+nn] = ex[(mm*(sizeY)+nn)*(sizeZ)+pp+1];
    }
  }
  for (mm = 0; mm < sizeX; ++mm){
    for (nn = 0; nn < sizeY - 1; ++nn){
      ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp] = eyz0[mm*(sizeY-1)+nn] + abccoef *
        (ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp+1] - ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp]);
      eyz0[mm*(sizeY-1)+nn] = ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp+1];
    }
  }

  /* ABC at "z1" (top) */
  pp = sizeZ - 1;
  for (mm = 0; mm < sizeX - 1; ++mm){
    for (nn = 0; nn < sizeY; ++nn){
      ex[(mm*(sizeY)+nn)*(sizeZ)+pp] = exz1[mm*(sizeY)+nn] + abccoef *
        (ex[(mm*(sizeY)+nn)*(sizeZ)+pp-1] - ex[(mm*(sizeY)+nn)*(sizeZ)+pp]);
      exz1[mm*(sizeY)+nn] = ex[(mm*(sizeY)+nn)*(sizeZ)+pp-1];
    }
  }
  for (mm = 0; mm < sizeX; ++mm){
    for (nn = 0; nn < sizeY - 1; ++nn){
      ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp] = eyz1[mm*(sizeY - 1)+nn] + abccoef *
        (ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp-1] - ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp]);
      eyz1[mm*(sizeY - 1)+nn] = ey[((mm) * (sizeY - 1) + nn) * sizeZ + pp-1];
    }
  }
  return;
}                   /* end updateABC() */
