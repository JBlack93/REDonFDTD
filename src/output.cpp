#include <array>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "REDonFDTD/output.hpp"

using namespace std;

static int temporalStride = -2, startTime;

void REDonFDTD::writeTo(std::array<double,3> position, float gamma, int mode)
{
  using namespace std;
  ofstream myfile;

  if (mode == 0)   {  myfile.open("xPos.txt", ios::trunc);  }
  else             {  myfile.open("xPos.txt", ios::app);  }
  myfile << position[0] << "\n";
  myfile.close();

  if (mode == 0)   {  myfile.open("yPos.txt", ios::trunc);  }
  else             {  myfile.open("yPos.txt", ios::app);  }
  myfile << position[1] << "\n";
  myfile.close();

  if (mode == 0)   {  myfile.open("zPos.txt", ios::trunc);  }
  else             {  myfile.open("zPos.txt", ios::app);  }
  myfile << position[2] << "\n";
  myfile.close();

  if (mode == 0)   {  myfile.open("Gamma.txt", ios::trunc);  }
  else             {  myfile.open ("Gamma.txt", ios::app);  }
  myfile << gamma << "\n";
  myfile.close();
}

void REDonFDTD::writeSingleValue(float value, const char* filename, int mode){
  ofstream myfile;
  if (mode == 0)   {  myfile.open(filename, ios::trunc);  }
  else             {  myfile.open(filename, ios::app);    }
  myfile << value << "\n";
  myfile.close();
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


void REDonFDTD::initialiseSlice(Mesh *g){
  int choice;
  printf("Do you want 2D slices of the 3D grid? (1=yes, 0=no) ");
  scanf("%d", &choice);
  if (choice == 0){
    temporalStride = -1;
    return;
  }

  remove( "dimensions1.txt" );
  remove( "dimensions2.txt" );
  remove( "ExXZ.txt" );
  remove( "ExYZ.txt" );
  int numberSteps = (g->maxTime)/(g->timeStep);
  printf("Duration of simulation is %d steps.\n", numberSteps);
  printf("Enter start time and temporal stride: ");
  scanf(" %d %d", &startTime, &temporalStride);
  return;
}        /* end initialiseSlice() */



void REDonFDTD::Slice(Mesh *g){
  ofstream myfile;
  /* ensure temporal stride set to a reasonable value */
  if (temporalStride == -1)   return;

  if (temporalStride < -1)
  {
    fprintf(stderr,
            "Slice: initialiseSlice must be called before Slice.\n"
            "Temporal stride must be set to positive value.\n");
    exit(-1);
  }


  int arg = static_cast<int>(g->time - startTime)/(g->timeStep);
  /* get snapshot if temporal conditions met */
  if (g->time >= startTime && arg % temporalStride == 0){

    /************ write the constant-x slice ************/

    /* write dimensions to output file */
    writeSingleValue(g->sizeY, "dimensions1.txt", 1);
    writeSingleValue(g->sizeZ, "dimensions1.txt", 1);
    writeSingleValue(g->maxTime, "dimensions1.txt",1);
    writeSingleValue(g->timeStep, "dimensions1.txt", 1);
    /* write remaining data */
    int mm = (g->sizeX - 1) / 2;
    for (int pp = 0; pp < g->sizeZ; ++pp){
      for (int nn = 0; nn < g->sizeY; ++nn){
        writeSingleValue(g->ex[(mm * (g->sizeY) + nn) * (g->sizeZ) + pp], "ExYZ.txt", 1);  // write out float value
      }
    }
  }              // close file

  /************ write the constant-y slice ************/

  /* write dimensions to output file */
  writeSingleValue((g->sizeX-1), "dimensions2.txt", 1);
  writeSingleValue(g->sizeZ, "dimensions2.txt", 1);
  writeSingleValue(g->maxTime, "dimensions2.txt",1);
  writeSingleValue(g->timeStep, "dimensions2.txt", 1);
  /* write remaining data */
  int nn = g->sizeY / 2;
  for (int pp = 0; pp < g->sizeZ; ++pp){
    for (int mm = 0; mm < g->sizeX - 1; ++mm){
      writeSingleValue(g->ex[(mm * (g->sizeY) + nn) * (g->sizeZ) + pp], "ExXZ.txt", 1);   // write the float
    }
  }
  return;
} /* end Slice() */
