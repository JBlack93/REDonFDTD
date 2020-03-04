/** @file utilities.hpp
 *  @brief Header file containing std::array manipulation functions */
#pragma once
#include <array>

namespace REDonFDTD {

  namespace util {
//! @{
/** @brief Calculate the Cross product between two 3-arrays
 *  @param array1      Array1
 *  @param array2      Array2
 *  @returns     Cross product of Array1 x Array2
 */
    std::array<double,3> cross(std::array<double,3> array1, std::array<double,3> array2);
/** @brief Calculate the norm of a 3 array
 *  @param a     Array to calculate norm of
 *  @returns     Norm of a (||a||)
 */
    std::array<double,3> norm(std::array<double,3> a);
/** @brief Calculate the dot product between two 3-arrays
 *  @param array1      Array1
 *  @param array2      Array2
 *  @returns     dot product of Array1 dot Array2
 */
    double dot(std::array<double,3> array1, std::array<double,3> array2);
/** @brief Calculate the magnitude of a 3 array
 *  @param a     Array to calculate magnitude of
 *  @returns     Magnitude of a (|a|)
 */
    double magnitude(std::array<double,3> a);
  }
}
