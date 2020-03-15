/** @file particle.hpp
 *  @brief Contains the Particle class */
#pragma once
#include <algorithm>
#include <array>

#include "REDonFDTD/config.hpp"
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/source.hpp"
#include "REDonFDTD/utilities.hpp"

namespace REDonFDTD {

//! @brief Particle struct contains all necessary information for updating the position of the particle.
  class Particle: public source {
  public:
    Particle() = delete;
    Particle(Mesh * g);
    Particle(Mesh * g, config configuration);
    ~Particle() = default;

/** @brief Update values of a particle at the end of a timestep
 *  @param g        Mesh in which particle lives
 */
    void timeAdvanceValues(Mesh *g);

  private:
    double charge = 1.6e-19;
    double mass = 1.67262178e-27;
    double prevGamma =1.;
    double gamma =1.;
    double futGamma=1.;

    std::array<double,3> prevPos = {0.};
    std::array<double,3> prevVel = {0.};
    std::array<double,3> prevAcc = {0.};

    std::array<double,3> futPos = {0.};
    std::array<double,3> futVel = {0.};
    std::array<double,3> futAcc = {0.};

/** @brief Calculate gamma from a velocity
 *  @param g              Mesh particle is present in
 *  @returns              gamma which corresponds to velocity
 */
    double findGamma(Mesh * g);

/** @brief Find energy radiated
 *  @param g        Mesh in which particle lives
 *  @returns        Energy which is radiated away
 */
    double powerRadiated(Mesh * g);

/** @brief Calculate Lorentz force felt by particle
 *  @param g        Mesh in which particle lives
 *  @returns        Force felt by particle
 */
    std::array<double,3> lorentzForce(Mesh *g);

/** @brief Calculate the E-Field produced by Particle on a particular point in S-T
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    std::array<double,3> eFieldProduced(Mesh *g, double x, double y, double z);

/** @brief Calculate the B-Field produced by Particle on a particular point in S-T
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param eField   Corresponding Electric Field
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    std::array<double,3> bFieldProduced(Mesh *g, std::array<double,3> eField,
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
 *  @param g        Mesh in which particle is present
 */
    void findAcceleration(Mesh *g);

/** @brief Velocity after energy radiated
 *  @param g        Mesh in which particle lives
 */
    void velocityAfterRad(Mesh *g);

  };
}
