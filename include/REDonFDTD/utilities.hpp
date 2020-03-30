/** @file utilities.hpp
 *  @brief Header file containing std::array manipulation functions */
#pragma once
#include <array>

namespace REDonFDTD {

//! @brief Various functions to manipulate vectors and arrays for use within REDonFDTD
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

/** @brief Calculate the unit Vector from array
 *  @param a     Array to calculate unit vector
 *  @returns     Unit vector of a
 */
    std::array<double,3> unitVector(std::array<double,3> a);

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

/** @brief Calculate the distance between two locations
 *  @param pos1      Position1
 *  @param pos2      Position2
 *  @returns     Distance between two positions
 */
    double distance(std::array<double,3> pos1, std::array<double,3> pos2);

/** @brief Calculate the theta between two arrays
 *  @param array1      Array1
 *  @param array2      Array2
 *  @returns     Theta between Array1 and Array2
 */
    double theta(std::array<double,3> array1, std::array<double,3> array2);
  }
}
