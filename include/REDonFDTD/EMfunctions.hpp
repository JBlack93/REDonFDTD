/** @file EMfunctions.hpp
 *  @brief Header file with all EM function declarations */

#include <vector>
#include "REDonFDTD/particleInit.hpp"
#include "REDonFDTD/meshInit.hpp"

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
