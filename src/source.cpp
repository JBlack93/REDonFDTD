#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include "include/REDonFDTD/prototypes.hpp"
#include "include/REDonFDTD/macroSetUp.hpp"
#include "include/REDonFDTD/memAllocation.hpp"



static double cdtds;

/* initialize source-function variables */
void initialiseSource(Particle *p, Mesh *g)
{

    ALLOC_1D(p->prevPos,3,double)
    xPrevPos = (double) (SizeX-1)/2;
    yPrevPos = (double) (SizeY/2)-0.5;
    zPrevPos = (double) (SizeZ/2)-0.5;
    ALLOC_1D(p->prevVel,3,double)
    xPrevVel = 0;
    yPrevVel = 0;
    zPrevVel = 0;
    ALLOC_1D(p->prevAcc,3,double)
    xPrevAcc = 0;
    yPrevAcc = 0;
    zPrevAcc = 0;

    ALLOC_1D(p->position,3,double)
    xPosition = (double) (SizeX-1)/2-0.05;
    yPosition = (double) SizeY/2-0.05;
    zPosition = (double) SizeZ/2-0.05;
    ALLOC_1D(p->velocity,3,double)
    xVelocity = 0;
    yVelocity = 0.999*c;
    zVelocity = 0;
    ALLOC_1D(p->acceleration,3,double)
    xAcceleration = 0;
    yAcceleration = 0;
    zAcceleration = 0;

    ALLOC_1D(p->futPos,3,double)
    xFutPos = 0;
    yFutPos = 0;
    zFutPos = 0;
    ALLOC_1D(p->futVel,3,double)
    xFutVel = 0;
    yFutVel = 0;
    zFutVel = 0;
    ALLOC_1D(p->futAcc,3,double)
    xFutAcc = 0;
    yFutAcc = 0;
    zFutAcc = 0;

    ALLOC_1D(p->coordinates,6,int)
    coord(0) =  floor(xPosition);        // Set the array element to the lower x coordinate
    coord(1) =  floor(yPosition);        // Set the array element to the lower y coordinate
    coord(2) =  floor(zPosition);        // Set the array element to the lower z coordinate
    coord(3) =  ceil(xPosition);         // Set the array element to the higher x coordinate
    coord(4) =  ceil(yPosition);         // Set the array element to the higher y coordinate
    coord(5) =  ceil(zPosition);         // Set the array element to the higher z coordinate

    Mass = 1.67262178*pow(10,-27);
    Charge = 1.6*pow(10,-19);
    PrevGamma = 1;
    Gamma = 1;
    FutGamma = 1;
}

/* Calculate the 6 points on the axes which produce
 * the 8 grid points closest to the point charge.
 */
void findCell(Particle *p)
{
    coord(0) = floor(xPosition);    // These are the lower values
    coord(1) = floor(yPosition);    // of the coordinates in the cell
    coord(2) = floor(zPosition);    // which the particle resides in

    coord(3) = ceil(xPosition);     // These are the higher values
    coord(4) = ceil(yPosition);     // of the coordinates in the cell
    coord(5) = ceil(zPosition);     // which the particle resides in
    }

/* Changes the the electric and magnetic field at 8 difference points based on
 * point paths movement through the mesh. Most key function in entire operation
 */
void sourceFunction(Particle *p, Mesh *g)
{
    findCell(p);
    for (unsigned i=0; i<2; i++)
    {
        for (unsigned n=0; n<2; n++)
        {
            for (unsigned m=0; m<2; m++)
            {

            int a = 3*i;       // Simply labels of the coordinate array which
            int b = 1+3*n;     // correspond to appropriate coordinates such
            int c = 2+3*m;     // that calculations can be done at all 8 points

            vct eField(3);
            vct bField(3);
            eField = eFieldProduced(p, coord(a), coord(b), coord(c));
            bField = bFieldProduced(p, eField, coord(a), coord(b), coord(c));
  /*          std::cout <<xPosition<<std::endl;
            std::cout <<(SizeX-1)/2-0.05<<std::endl;
            std::cout <<coord(a)<<std::endl;
  */        Ex(coord(a), coord(b), coord(c)) += eField[0];      // Calculation of the effect which
            Ey(coord(a), coord(b), coord(c)) += eField[1];      // charged particle has on each of
            Ez(coord(a), coord(b), coord(c)) += eField[2];      // directions of E-Field

            Hx(coord(a), coord(b), coord(c)) += bField[0]/Mu_0;      // Calculation of the effect which
            Hy(coord(a), coord(b), coord(c)) += bField[1]/Mu_0;      // charged particle has on each of
            Hz(coord(a), coord(b), coord(c)) += bField[2]/Mu_0;      // these directions of the H-Field

            }
        }
    }// amplitude of change in field due to source
}

vct eFieldProduced(Particle *p, double x, double y, double z)
{
    typedef boost::numeric::ublas::vector<double> vct;
    using namespace boost::numeric::ublas;

    vct gridRadius(3);
    vct sourceRadius(3);
    vct dirU(3);
    vct gridToSource(3);
    vct velocity(3);
    vct acceleration(3);

    gridRadius = iniVector(x,y,z);
    sourceRadius = iniVector(xPosition,yPosition,zPosition);
    velocity   = iniVector(xVelocity,yVelocity,zVelocity);
    acceleration = iniVector(xAcceleration, yAcceleration, zAcceleration);


    gridToSource = gridRadius - sourceRadius;
    double gridToSourceMag = magnitude(gridToSource);                       //STILL NEED TO MAKE THIS EVALUATED AT RETARDED
    dirU = c*gridToSource/(gridToSourceMag) - velocity;                     //TIME... NOT SURE YET.
    double dotGridSourceU = dot(gridToSource, dirU);


    double prefactor = Charge/(4*M_PI*epsilon_0);
    double secondFactor = gridToSourceMag/(pow(dotGridSourceU/gridToSourceMag,3));
    vct firstTerm(3);
    firstTerm = (pow(c,2)-dot(velocity,velocity))*dirU;
    vct secondTerm(3);
    secondTerm = cross(gridToSource, cross(dirU, acceleration))/gridToSourceMag;
    vct eField(3);
    eField = prefactor*secondFactor*(firstTerm+secondTerm);
    return eField;
}



vct bFieldProduced(Particle *p, vct eField, double x, double y, double z)
{
    vct bField(3);
    vct gridRadius(3);
    vct sourceRadius(3);
    vct gridToSource(3);

    gridRadius = iniVector(x,y,z);
    sourceRadius = iniVector(xPosition,yPosition,zPosition);
    gridToSource = gridRadius - sourceRadius;
    double gridToSourceMag = magnitude(gridToSource);

    bField = (1/(c*gridToSourceMag))*(cross(gridToSource, eField));

    return bField;
}
