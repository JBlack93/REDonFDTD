/** @file particle.hpp
 *  @brief Contains the Particle class */
#pragma once
#include <algorithm>

#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/utilities.hpp"

namespace REDonFDTD {

//! @brief Particle struct contains all necessary information for updating the position of the particle.
  class Particle {
  public:
    Particle(Mesh * g);
    ~Particle() = default;

/** @brief Calculate effect Particle has on neighbouring Mesh Points
 *  @param p        Particle which we need to calculate effect of
 *  @param g        Mesh upon which the particle's effects are felt
 */
    void sourceFunction(Mesh *g);

/** @brief Calculate the E-Field produced by Particle on a particular point in S-T
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    std::vector<double> eFieldProduced(Mesh *g, double x, double y, double z);

/** @brief Calculate the B-Field produced by Particle on a particular point in S-T
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param eField   Corresponding Electric Field
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    std::vector<double> bFieldProduced(Mesh *g, std::vector<double> eField,
                                       double x, double y, double z);

/** @brief Calculate next position of a particle using FD method.
 *  @param g        Mesh in which particle is present
 */
    void newPositionTaylor(Mesh *g);

/** @brief Calculate next velocity of a particle using FD method.
 *  @param g        Mesh in which particle is present
 */
    void newVelocityTaylor(Mesh *g);

/** @brief Update Acceleration for particle
 *  @param force    External force on particle
 */
    void findAcceleration(std::vector<double> force);

/** @brief Calculate Lorentz force felt by particle
 *  @param g        Mesh in which particle lives
 *  @returns        Force felt by particle
 */
    std::vector<double> lorentzForce(Mesh *g);

/** @brief Find energy radiated
 *  @param g        Mesh in which particle lives
 *  @returns        Energy which is radiated away
 */
    double powerRadiated(Mesh * g);

/** @brief Velocity after energy radiated
 *  @param g        Mesh in which particle lives
 *  @param powerRad Energy which is radiated away
 */
    void velocityAfterRad(Mesh *g, double powerRad);

    double charge,     mass;
    double prevGamma,  gamma,     futGamma;
    double *prevPos,   *prevVel,  *prevAcc;
    double *position,  *velocity, *acceleration;
    double *futPos,    *futVel,   *futAcc;
    int *coordinates;

  private:
/** @brief Calculate the 6 points on the axes which give closest grid points
 */
    void findCell();
/** @brief Calculate gamma from a velocity
 *  @param g              Mesh particle is present in
 *  @returns              gamma which corresponds to velocity
 */
    double findGamma(Mesh * g);

  };
}
