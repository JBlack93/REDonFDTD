/** @file EMfunctions.hpp
 *  @brief Header file with all EM function declarations */

#include <array>
#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/mesh.hpp"

namespace REDonFDTD {

/** @brief Advance time by 1/2 a step (for staggering between E+B)
 *  @param p        Particle to be advanced
 *  @param g        Mesh to be advanced
 */
  void halfTimeStep(Particle *p, Mesh *g);
}
