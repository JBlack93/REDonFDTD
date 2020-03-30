/** @file source.hpp
 *  @brief Contains the abstract source class, which also includes factory method */
#pragma once
#include <algorithm>

#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/utilities.hpp"

namespace REDonFDTD {

  enum sourceType: int {
    src_Particle=0, src_ricker=1
  };

//! @brief Generic abstract virtual source class.
  class source {
  public:
    source() = default;
    source(Mesh *g);
    ~source() = default;
    static source * Create(Mesh *g, config configuration, sourceType Type);

/** @brief Calculate effect source has on neighbouring Mesh Points
 *  @param g                 Mesh upon which the source's effects are felt
 *  @param analyticRange     Range for which sources effect calculated analytically
 */
    void sourceFunction(Mesh *g, int analyticRange);

/** @brief Update values of a source at the end of a timestep
 *  @param g        Mesh in which particle lives
 */
    virtual void timeAdvanceValues(Mesh *g) = 0;

    void InitialiseMesh(Mesh *g);

  protected:
    std::array<double,3> position = {0.};       //!< @brief Position of source
    std::array<double,3> velocity = {0.};       //!< @brief Velocity of source
    std::array<double,3> acceleration = {0.};   //!< @brief Acceleration of source
    std::array<int,6> coordinates = {0};        //!< @brief grid coordinates surrounding source


/** @brief Calculate the 6 points on the axes which give closest grid points
 */
    void findCell(Mesh *g);

/** @brief Calculate field produced by constant velocity particle (see Eq 4.12 Thesis)
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    virtual std::array<double,3> velocityEField(Mesh *g, double x, double y, double z);

/** @brief Calculate the E-Field produced by source on a particular point in S-T
 *  @param g        Mesh upon which the particle's effects are felt
 *  @param x        x-position of grid point
 *  @param y        y-position of grid point
 *  @param z        z-position of grid point
 */
    virtual std::array<double,3> eFieldProduced(Mesh *g, double x, double y, double z) = 0;

/** @brief Calculate the B-Field produced by source on a particular point in S-T
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
