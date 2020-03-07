/** @file output.hpp
 *  @brief Output file handling function declarations */
#pragma once
#include <cstdio>
#include <array>

#include "REDonFDTD/mesh.hpp"

namespace REDonFDTD {

/** @brief Output generic value at position in grid
 *  @param x                x Position of component
 *  @param y                y Position of component
 *  @param z                z Position of component
 *  @param Component        Field Component value
 *  @param filename         Field Component value
 *  @param mode             if ==0, truncate, else append
 */
  void writeComponent(double x, double y, double z, double Component,
                      const char* filename, int mode);

/** @brief Output E-Field for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeEx(Mesh *g, int mode);

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

/** @brief Initialise basic output
 *  @param g        Space-time mesh to output
 */
  void initialiseSlice(Mesh *g);
/** @brief Output slice
 *  @param g        Space-time mesh to output
 */
  void Slice(Mesh *g);
}
