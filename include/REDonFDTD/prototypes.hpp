/** @file prototypes.hpp
 *  @brief Generic header file with all function declarations */
#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include "REDonFDTD/particleInit.hpp"
#include "REDonFDTD/meshInit.hpp"


//! @{
// meshInit.cpp//
/** @brief Set up initial conditions in the Mesh
    @param g        Space-time mesh to be initialised
 */
void initialiseMesh(Mesh *g);
//! @}


//! @{
//update3d.cpp//
/** @brief Update the E-Field in the space-time Mesh
    @param g        Space-time mesh to be updated
 */
void updateE(Mesh *g);
/** @brief Update the H-Field in the space-time Mesh
    @param g        Space-time mesh to be updated
 */
void updateH(Mesh *g);
//! @}

//! @{
//ABCsetup.cpp//
/** @brief abc initialization function
    @param g        Space-time mesh to be initialised
 */
void initialiseABC(Mesh *g);
/** @brief function that applies ABC -- called once per time step
    @param g        Space-time mesh to be updated
 */
void updateABC(Mesh *g);
//! @}

//! @{
//slice.cpp//
/** @brief Initialise basic output
    @param g        Space-time mesh to output
 */
void initialiseSlice(Mesh *g);
/** @brief Output slice
    @param g        Space-time mesh to output
 */
void Slice(Mesh *g);
//! @}

//! @{
//ricker.cpp//
/** @brief initialize ricker source-function variables
 *  @param g       Space-time Mesh in which source will be present
 */
void initialiseEzInc(Mesh *g);
/** @brief calculate source function at given time and location
 *  @param time       Time at which source function calculated
 *  @param location   Location at which source function calculated
 */
double ezInc(double time, double location);
//! @}

//! @{
//source.cpp//

/** @brief Calculate the 6 points on the axes which give closest grid points
 *  @param p      For which location needs to be found
 */
void findCell(Particle *p);

/** @brief Calculate effect Particle has on neighbouring Mesh Points
 *  @param p        Particle which we need to calculate effect of
 *  @param g        Mesh upon which the particle's effects are felt
 */
void sourceFunction(Particle *p,Mesh *g);

/** @brief Calculate the E-Field produced by Particle on a particular point in S-T
 *  @param p        Particle which we need to calculate effect of
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
std::vector<double> eFieldProduced(Particle *p, Mesh *g, double x, double y, double z);

/** @brief Calculate the B-Field produced by Particle on a particular point in S-T
    @param p        Particle which we need to calculate effect of
 *  @param g        Mesh upon which the particle's effects are felt
    @param eField   Corresponding Electric Field
    @param x        x-position of grid point
    @param y        y-position of grid point
    @param z        z-position of grid point
 */
std::vector<double> bFieldProduced(Particle *p, Mesh* g, std::vector<double> eField, double x, double y, double z);
//! @}

//! @{
//DataAnalysis.cpp//
/** @brief Calculate the Cross product between two 3-vectors
 *  @param vector1      Vector1
 *  @param vector2      Vector2
 *  @returns     Cross product of Vector1 x Vector2
 */
std::vector<double> cross(std::vector<double> vector1, std::vector<double> vector2);
/** @brief Calculate the norm of a 3 vector
 *  @param a     Vector to calculate norm of
 *  @returns     Norm of a (||a||)
 */
std::vector<double> norm(std::vector<double> a);
/** @brief Calculate the dot product between two 3-vectors
 *  @param vector1      Vector1
 *  @param vector2      Vector2
 *  @returns     dot product of Vector1 dot Vector2
 */
double dot(std::vector<double> vector1, std::vector<double> vector2);
/** @brief Calculate the magnitude of a 3 vector
 *  @param a     Vector to calculate magnitude of
 *  @returns     Magnitude of a (|a|)
 */
double magnitude(std::vector<double> a);
/** @brief Output particle position and gamma value
 *  @param position         Particle Position
 *  @param gamma            Particle Gamma
 *  @param mode             if ==0, truncate, else append
 */
void writeTo(std::vector<double> position, float gamma, int mode);
/** @brief Output E-Field for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
void writeEField(Mesh *g, int mode);
/** @brief Output H-Field for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
void writeHField(Mesh *g, int mode);
/** @brief Output generic float value to a specified file
 *  @param value         Value to be outputted
 *  @param filename      File to be outputted to
 *  @param mode          if ==0, truncate, else append
 */
void writeSingleValue(float value, const char* filename, int mode);
//! @}

//! @{
//EMFunctions.cpp//
/** @brief Calculate next position of a particle using FD method.
 *  @param p        Particle whose position needs updating
 *  @param g        Mesh in which particle is present
 */
void newPositionTaylor(Particle *p, Mesh *g);
/** @brief Calculate next velocity of a particle using FD method.
 *  @param p        Particle whose velocity needs updating
 *  @param g        Mesh in which particle is present
 */
void newVelocityTaylor(Particle *p, Mesh *g);
/** @brief Update Acceleration for particle
 *  @param p        Particle on which an external force is acting
 *  @param force    External force on particle
 */
void findAcceleration(Particle *p, std::vector<double> force);
/** @brief Calculate Lorentz force felt by particle
 *  @param p        Particle which force will be calculated for
 *  @param g        Mesh in which particle lives
 *  @returns        Force felt by particle
 */
std::vector<double> lorentzForce(Particle *p, Mesh *g);
/** @brief Velocity after energy radiated
 *  @param p        Particle which will radiate energy
 *  @param powerRad Energy which is radiated away
 */
void velocityAfterRad(Particle *p, Mesh *g, double powerRad);
/** @brief Calculate gamma from a velocity
 *  @param velocity       Velocity to convert to gamma
 *  @returns              gamma which corresponds to velocity
 */
double findGamma(std::vector<double> velocity);
/** @brief Find energy radiated
 *  @param p        Particle which will radiate energy
 *  @returns        Energy which is radiated away
 */
double powerRadiated(Particle *p, Mesh *g);

/** @brief Update values of a particle at the end of a timestep
 *  @param p        Particle to be updated
 */
void timeAdvanceValues(Particle *p);
/** @brief Advance time by 1/2 a step (for staggering between E+B)
 *  @param p        Particle to be advanced
 *  @param g        Mesh to be advanced
 */
void halfTimeStep(Particle *p, Mesh *g);
//! @}
