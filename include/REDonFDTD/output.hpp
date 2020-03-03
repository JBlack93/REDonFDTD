/** @file output.hpp
 *  @brief Output file handling function declarations */
#pragma once
#include <cstdio>
#include <vector>

#include "REDonFDTD/meshInit.hpp"

void writeTo(std::vector<double> position, float gamma, int mode);
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
