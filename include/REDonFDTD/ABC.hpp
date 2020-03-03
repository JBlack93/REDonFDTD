/** @file ABC.hpp
 *  @brief ABC boundary condition declarations */
#pragma once

#include "REDonFDTD/mesh.hpp"

namespace REDonFDTD {

/** @brief abc initialization function
    @param g        Space-time mesh to be initialised
*/
  void initialiseABC(Mesh *g);
/** @brief function that applies ABC -- called once per time step
 *  @param g        Space-time mesh to be updated
 */
  void updateABC(Mesh *g);
}
