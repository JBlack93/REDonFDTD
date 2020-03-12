/** @file ricker.hpp
 *  @brief Functions for Ricker source declarations */
#pragma once

#include <array>
#include "REDonFDTD/config.hpp"
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/source.hpp"

namespace REDonFDTD {

  class ricker: public source {
  public:
    ricker(Mesh *g, double pointspwave);
    ricker(Mesh *g, double pointspwave, config configuration);
    ~ricker() = default;

/** @brief Advance values pertaining to ricker source
 *  @param g       Space-time Mesh in which source will be present
 */
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

    double ppw;

  };
}
