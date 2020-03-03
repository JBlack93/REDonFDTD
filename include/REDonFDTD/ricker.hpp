/** @file ricker.hpp
 *  @brief Functions for Ricker source declarations */
#pragma once

#include "REDonFDTD/mesh.hpp"

/** @brief initialize ricker source-function variables
 *  @param g       Space-time Mesh in which source will be present
 */
void initialiseEzInc(Mesh *g);
/** @brief calculate source function at given time and location
 *  @param time       Time at which source function calculated
 *  @param location   Location at which source function calculated
 */
double ezInc(double time, double location);
