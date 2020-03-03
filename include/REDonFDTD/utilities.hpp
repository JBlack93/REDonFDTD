/** @file utilities.hpp
 *  @brief Header file containing std::vector manipulation functions */
#pragma once
#include <vector>

namespace manip {
//! @{
/** @brief Calculate the Cross product between two 3-vectors
 *  @param vector1      Vector1
 *  @param vector2      Vector2
 *  @returns     Cross product of Vector1 x Vector2
 */
std::vector<double> cross(std::vector<double> vector1, std::vector<double> vector2);
/** @brief Calculate the norm of a 3 vector
 *  @param a     Vector to calculate norm of
 *  @returns     Norm of a (||a||)
 */
std::vector<double> norm(std::vector<double> a);
/** @brief Calculate the dot product between two 3-vectors
 *  @param vector1      Vector1
 *  @param vector2      Vector2
 *  @returns     dot product of Vector1 dot Vector2
 */
double dot(std::vector<double> vector1, std::vector<double> vector2);
/** @brief Calculate the magnitude of a 3 vector
 *  @param a     Vector to calculate magnitude of
 *  @returns     Magnitude of a (|a|)
 */
double magnitude(std::vector<double> a);
/** @brief Output particle position and gamma value
 *  @param position         Particle Position
 *  @param gamma            Particle Gamma
 *  @param mode             if ==0, truncate, else append
 */
}
