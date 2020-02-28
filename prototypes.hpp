#ifndef _PROTOTYPES_H
#define _PROTOTYPES_H

#include <boost/numeric/ublas/vector.hpp>
typedef boost::numeric::ublas::vector<double> vct;
using namespace boost::numeric::ublas;

#include "meshInit.hpp"
#include "particleInit.hpp"


static double c = 2.99792458*pow(10,8);
static double epsilon_0 = 8.85418782*pow(10,-12);
static double Mu_0 = 4*M_PI*pow(10,-7);


//Function prototypes//
//meshInit.cpp//
void initialiseMesh(Mesh *g);

//update3d.cpp//
void updateE(Mesh *g);
void updateH(Mesh *g);

//ABCsetup.cpp//
void initialiseABC(Mesh *g);
void updateABC(Mesh *g);

//Snapshot.c//
void initialiseSlice(Mesh *g);
void Slice(Mesh *g);

//ricker.cpp//
void initialiseEzInc(Mesh *g);
double ezInc(double time, double location);

//source.cpp//
void findCell(Particle *p);
void initialiseSource(Particle *p, Mesh *g);
void sourceFunction(Particle *p,Mesh *g);
vct eFieldProduced(Particle *p, double x, double y, double z);
vct bFieldProduced(Particle *p, vct eField, double x, double y, double z);

//DataAnalysis.cpp//
vct iniVector(double x, double y,double z);
vct cross(vct vector1, vct vector2);
vct norm(vct a);
double dot(vct vector1, vct vector2);
double magnitude(vct a);
void writeTo(vct position, float gamma, int mode);
void writeEField(Mesh *g, int mode);
void writeHField(Mesh *g, int mode);
void writeSingleValue(float value, const char* filename, int mode);

//EMFunctions.cpp//
void newPositionTaylor(Particle *p, Mesh *g);
void newVelocityTaylor(Particle *p, Mesh *g);
void findAcceleration(Particle *p, vct force);
vct lorentzForce(Particle *p, Mesh *g);
void velocityAfterRad(Particle *p, double powerRad);
double findGamma(vct velocity);
double powerRadiated(Particle *p);
void timeAdvanceValues(Particle *p);
void halfTimeStep(Particle *p, Mesh *g);

#endif
