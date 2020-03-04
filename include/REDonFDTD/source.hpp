/** @file particle.hpp
 *  @brief Contains the Particle class */
#pragma once
#include <algorithm>

#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/utilities.hpp"

namespace REDonFDTD {

//! @brief Particle struct contains all necessary information for updating the position of the particle.
  class source {
  public:
    source();
    ~source() = default;

/** @brief Calculate effect Particle has on neighbouring Mesh Points
 *  @param g        Mesh upon which the particle's effects are felt
 */
    void sourceFunction(Mesh *g);

/** @brief Update values of a particle at the end of a timestep
 *  @param g        Mesh in which particle lives
 */
    virtual void timeAdvanceValues(Mesh *g) = 0;

  protected:
    std::array<double,3> position{0,0,0};
    std::array<double,3> velocity{0,0,0};
    std::array<double,3> acceleration{0,0,0};
    std::array<int,6> coordinates;

/** @brief Calculate the 6 points on the axes which give closest grid points
 */
    void findCell();

/** @brief Calculate the E-Field produced by Particle on a particular point in S-T
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    virtual std::array<double,3> eFieldProduced(Mesh *g, double x, double y, double z) = 0;

/** @brief Calculate the B-Field produced by Particle on a particular point in S-T
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param eField   Corresponding Electric Field
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    virtual std::array<double,3> bFieldProduced(Mesh *g, std::array<double,3> eField,
                                       double x, double y, double z) = 0;

  };
}
