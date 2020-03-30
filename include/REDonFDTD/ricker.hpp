/** @file ricker.hpp
 *  @brief Functions for Ricker source declarations */
#pragma once

#include <array>
#include "REDonFDTD/config.hpp"
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/source.hpp"

namespace REDonFDTD {

//! @brief Class containint basic ricker source
  class ricker: public source {
  public:
    ricker(Mesh *g, double pointspwave);
    ricker(Mesh *g, config configuration);
    ~ricker() = default;

//! @brief Advance values pertaining to ricker source
    void timeAdvanceValues(Mesh * /*g*/);

private:
    std::array<double,3> eFieldProduced(Mesh *g, double x, double y, double z);
    std::array<double,3> bFieldProduced(Mesh * /*g*/, std::array<double,3> /*eField*/,
                                                       double /*x*/, double /*y*/, double /*z*/);
/** @brief calculate source function at given time and location
 *  @param time       Time at which source function calculated
 *  @param location   Location at which source function calculated
 */
    double ezInc(Mesh * g, double location);

//! @brief Basic Points-per-wave parameter of the ricker source.
    double ppw;

  };
}
