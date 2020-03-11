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
 *  @param Component        Field Component value
 *  @param filename         Field Component value
 *  @param mode             if ==0, truncate, else append
 */
  void writeComponent(double x, double y, double Component,
                      std::string filename, int mode);

/** @brief Output Ex component of E-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeExXY(Mesh *g, int mode);

/** @brief Output Ey component of E-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeEyXY(Mesh *g, int mode);

/** @brief Output Ez component of E-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeEzXY(Mesh *g, int mode);

/** @brief Output |E| of E-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeEMagXY(Mesh *g, int mode);

/** @brief Output Hx component of H-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeHxXY(Mesh *g, int mode);

/** @brief Output Hy component of H-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeHyXY(Mesh *g, int mode);

/** @brief Output Hz component of H-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeHzXY(Mesh *g, int mode);

/** @brief Output |H| of H-Field in Central XY plane for a a particular time
 *  @param g                Mesh to be outputted
 *  @param mode             if ==0, truncate, else append
 */
  void writeHMagXY(Mesh *g, int mode);

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

/** @brief Utilise GnuPlot for output
 *  @param g                Mesh to be outputted
 */
  void Plot(Mesh *g);

}
