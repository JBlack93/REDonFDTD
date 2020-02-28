/* This Header file contains all the necessary manipulation of data
 * functions. Including writing to .txt files.
 */
#include <fstream>
#include <vector>
#include <cmath>
#include "include/REDonFDTD/macroSetUp.hpp"

std::vector<double> iniVector(double x, double y,double z)
{
    std::vector<double> Vector(3);
    Vector[0]=x; Vector[1]=y; Vector[2]=z;
    return Vector;
}

std::vector<double> cross(std::vector<double> vector1, std::vector<double> vector2)
{
    std::vector<double> vector3 (3);
    vector3[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1];
    vector3[1] = vector1[2]*vector2[0] - vector1[0]*vector2[2];
    vector3[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0];

    return vector3;
}

double dot(std::vector<double> vector1, std::vector<double> vector2)
{
    float dotProduct=0;
    for (unsigned i=0; i< vector1.size(); i++)
        {
        dotProduct += vector1[i]*vector2[i];
        }

    return dotProduct;

}

double magnitude(std::vector<double> a)
{
    float mag;
    mag = std::sqrt(dot(a,a));
    return mag;
}

std::vector<double> norm(std::vector<double> a)
{
    float aMag = magnitude(a);
    for (unsigned i = 0; i < a.size(); ++ i)
        {
        a[i] = a[i]/aMag;
        }
    return a;
}

void writeTo(std::vector<double> position, float gamma, int mode)
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

void writeSingleValue(float value, const char* filename, int mode)
{
    using namespace std;
    ofstream myfile;
    if (mode == 0)   {  myfile.open(filename, ios::trunc);  }
    else             {  myfile.open(filename, ios::app);    }
    myfile << value << "\n";
    myfile.close();
}

void writeEField(Mesh *g, int mode)
{
    using namespace std;
    ofstream myfile;

    if (mode == 0)   {  myfile.open("Ex.txt", ios::trunc);  }
    else             {  myfile.open("Ex.txt", ios::app);    }
    for (signed i=0; i < (SizeX-1)*SizeY*SizeZ;i++)
    {             myfile << g->ex[i] << "\n";               }
    myfile.close();

    if (mode == 0)   {  myfile.open("Ey.txt", ios::trunc);  }
    else             {  myfile.open("Ey.txt", ios::app);    }
    for (signed i=0; i< (SizeX)*(SizeY-1)*SizeZ;i++)
    {             myfile << g->ey[i] << "\n";               }
    myfile.close();

    if (mode == 0)   {  myfile.open("Ez.txt", ios::trunc);  }
    else             {  myfile.open("Ez.txt", ios::app);    }
    for (signed i=0; i< (SizeX)*(SizeY)*(SizeZ-1);i++)
    {             myfile << g->ez[i] << "\n";               }
    myfile.close();
}

void writeHField(Mesh *g, int mode)
{
    using namespace std;
    ofstream myfile;

    if (mode == 0)   {  myfile.open("Hx.txt", ios::trunc);  }
    else             {  myfile.open("Hx.txt", ios::app);    }
    for (unsigned i=0; i< (SizeX-1)*SizeY*SizeZ;i++)
    {             myfile << g->hx[i] << "\n";               }
    myfile.close();

    if (mode == 0)   {  myfile.open("Hy.txt", ios::trunc);  }
    else             {  myfile.open("Hy.txt", ios::app);    }
    for (unsigned i=0; i< (SizeX)*(SizeY-1)*SizeZ;i++)
    {             myfile << g->hy[i] << "\n";               }
    myfile.close();

    if (mode == 0)   {  myfile.open("Hz.txt", ios::trunc);  }
    else             {  myfile.open("Hz.txt", ios::app);    }
    for (unsigned i=0; i< (SizeX)*(SizeY)*(SizeZ-1);i++)
    {             myfile << g->hz[i] << "\n";               }
    myfile.close();
}
