#include <array>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "REDonFDTD/output.hpp"
#include "gnuplot/gnuplot.hpp"
#include "REDonFDTD/utilities.hpp"

using namespace std;

void REDonFDTD::writeComponent(double x, double y, double Component,
                               std::string filename, int mode)
{
  ofstream myfile;
  if (mode == 0)   {  myfile.open(filename, ios::trunc);  }
  else             {  myfile.open(filename, ios::app);  }
  myfile <<x<<" "<<y<<" "<<Component<<endl;
  myfile.close();
}

void REDonFDTD::writeSingleValue(float value, const char* filename, int mode){
  ofstream myfile;
  if (mode == 0)   {  myfile.open(filename, ios::trunc);  }
  else             {  myfile.open(filename, ios::app);    }
  myfile << value << "\n";
  myfile.close();
}

void REDonFDTD::writeExXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/ExXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX - 1; ++mm){
    for (int nn = 0; nn < g->sizeY; ++nn){
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                          g->ex[(mm*g->sizeY+nn)*g->sizeZ+zcoord], filename, mode);
    }
  }
}

void REDonFDTD::writeEyXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/EyXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX; ++mm){
    for (int nn = 0; nn < g->sizeY-1; ++nn){
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                          g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+zcoord], filename, mode);
    }
  }
}

void REDonFDTD::writeEzXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/EzXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX; ++mm){
    for (int nn = 0; nn < g->sizeY; ++nn){
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                          g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+zcoord], filename, mode);
    }
  }
}

void REDonFDTD::writeEMagXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/EMagXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX - 1; ++mm){
    for (int nn = 0; nn < g->sizeY; ++nn){
        std::array<double,3> eField{g->ex[(mm*g->sizeY+nn)*g->sizeZ+zcoord],
                                   g->ey[(mm*(g->sizeY-1)+nn)*g->sizeZ+zcoord],
                                   g->ez[(mm*g->sizeY+nn)*(g->sizeZ-1)+zcoord]};
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                          util::magnitude(eField), filename, mode);
    }
  }
}


void REDonFDTD::writeHxXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/HxXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX; ++mm){
    for (int nn = 0; nn < g->sizeY - 1; ++nn){
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                                  g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+zcoord], filename, mode);
    }
  }
}

void REDonFDTD::writeHyXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/HyXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX-1; ++mm){
    for (int nn = 0; nn < g->sizeY; ++nn){
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                                  g->hy[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+zcoord], filename, mode);
    }
  }
}

void REDonFDTD::writeHzXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/HzXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX-1; ++mm){
    for (int nn = 0; nn < g->sizeY-1; ++nn){
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                                  g->hz[(mm*(g->sizeY-1)+nn)*(g->sizeZ)+zcoord], filename, mode);
    }
  }
}

void REDonFDTD::writeHMagXY(Mesh *g, int mode){
  const int zcoord = g->sizeZ/2;
  const int step = (g->time)/(g->timeStep);
  std::string filename = "output/HMagXY";
  filename.append(std::to_string(step));
  filename.append(".txt");
  for (int mm = 0; mm < g->sizeX - 1; ++mm){
    for (int nn = 0; nn < g->sizeY; ++nn){
        std::array<double,3> hField{g->hx[(mm*(g->sizeY-1)+nn)*(g->sizeZ-1)+zcoord],
                                   g->hy[(mm*(g->sizeY)+nn)*(g->sizeZ-1)+zcoord],
                                   g->hz[(mm*(g->sizeY-1)+nn)*(g->sizeZ)+zcoord]};
        REDonFDTD::writeComponent((g->dS)*mm, (g->dS)*nn,
                          util::magnitude(hField), filename, mode);
    }
  }
}



void REDonFDTD::writeEField(Mesh *g, int mode){
  ofstream myfile;

  if (mode == 0)   {  myfile.open("Ex.txt", ios::trunc);  }
  else             {  myfile.open("Ex.txt", ios::app);    }
  for (int i=0; i < (g->sizeX-1)*(g->sizeY)*(g->sizeZ);++i)
  {             myfile << g->ex[i] << "\n";               }
  myfile.close();

  if (mode == 0)   {  myfile.open("Ey.txt", ios::trunc);  }
  else             {  myfile.open("Ey.txt", ios::app);    }
  for (int i=0; i< (g->sizeX)*(g->sizeY-1)*(g->sizeZ);++i)
  {             myfile << g->ey[i] << "\n";               }
  myfile.close();

  if (mode == 0)   {  myfile.open("Ez.txt", ios::trunc);  }
  else             {  myfile.open("Ez.txt", ios::app);    }
  for (int i=0; i< (g->sizeX)*(g->sizeY)*(g->sizeZ-1);++i)
  {             myfile << g->ez[i] << "\n";               }
  myfile.close();
}

void REDonFDTD::writeHField(Mesh *g, int mode){
  ofstream myfile;

  if (mode == 0)   {  myfile.open("Hx.txt", ios::trunc);  }
  else             {  myfile.open("Hx.txt", ios::app);    }
  for (int i=0; i< (g->sizeX-1)*(g->sizeY)*(g->sizeZ);++i)
  {             myfile << g->hx[i] << "\n";               }
  myfile.close();

  if (mode == 0)   {  myfile.open("Hy.txt", ios::trunc);  }
  else             {  myfile.open("Hy.txt", ios::app);    }
  for (int i=0; i< (g->sizeX)*(g->sizeY-1)*(g->sizeZ);++i)
  {             myfile << g->hy[i] << "\n";               }
  myfile.close();

  if (mode == 0)   {  myfile.open("Hz.txt", ios::trunc);  }
  else             {  myfile.open("Hz.txt", ios::app);    }
  for (int i=0; i< (g->sizeX)*(g->sizeY)*(g->sizeZ-1);++i)
  {             myfile << g->hz[i] << "\n";               }
  myfile.close();
}

void REDonFDTD::Slice(Mesh *g){
  ofstream myfile;
  /************ write the constant-x slice ************/

  /* write dimensions to output file */
  writeSingleValue(g->sizeY, "output/dimensions1.txt", 1);
  writeSingleValue(g->sizeZ, "output/dimensions1.txt", 1);
  writeSingleValue(g->maxTime, "output/dimensions1.txt",1);
  writeSingleValue(g->timeStep, "output/dimensions1.txt", 1);
  /* write remaining data */
  int mm = (g->sizeX - 1) / 2;
  for (int pp = 0; pp < g->sizeZ; ++pp){
    for (int nn = 0; nn < g->sizeY; ++nn){
      writeSingleValue(g->ex[(mm * (g->sizeY) + nn) * (g->sizeZ) + pp], "output/ExYZ.txt", 1);  // write out float value
    }
  }
  // close file

/************ write the constant-y slice ************/

/* write dimensions to output file */
  writeSingleValue((g->sizeX-1), "output/dimensions2.txt", 1);
  writeSingleValue(g->sizeZ, "output/dimensions2.txt", 1);
  writeSingleValue(g->maxTime, "output/dimensions2.txt",1);
  writeSingleValue(g->timeStep, "output/dimensions2.txt", 1);
/* write remaining data */
  int nn = g->sizeY / 2;
  for (int pp = 0; pp < g->sizeZ; ++pp){
    for (int mm = 0; mm < g->sizeX - 1; ++mm){
      writeSingleValue(g->ex[(mm * (g->sizeY) + nn) * (g->sizeZ) + pp], "output/ExXZ.txt", 1);   // write the float
    }
  }

  return;
} /* end Slice() */

void REDonFDTD::Plot(Mesh *g, bool mode){
  REDonFDTD::writeExXY(g,mode);
  gnuplot::GnuplotPipe gp;

  gp.sendLine("set view map");
  gp.sendLine("set dgrid3d");
  gp.sendLine("set pm3d interpolate 50,50");
  gp.sendLine("splot 'output/ExXY50.txt' using 1:2:3 with pm3");
}
