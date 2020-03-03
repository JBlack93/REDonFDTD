/** @file memAllocation.hpp
 *  @brief memory allocation functions */
#pragma once

#include <cstdio>
#include <cstdlib>

namespace REDonFDTD {

/** @brief deprecated allocation function. Replace with class constructor
 */
  template<class T>
  inline T* ALLOC_1D(T* ptr, int x){
    ptr = static_cast<T*>(calloc(x, sizeof(T)));
    return ptr;
  }
/** @brief deprecated allocation function. Replace with class constructor
 */
  template<class T>
  inline T* ALLOC_2D(T* ptr, int x , int y){
    ptr = static_cast<T*>(calloc(x*y, sizeof(T)));
    return ptr;
  }
/** @brief deprecated allocation function. Replace with class constructor
 */
  template<class T>
  inline T* ALLOC_3D(T* ptr, int x, int y, int z){
    ptr = static_cast<T*>(calloc(x*y*z, sizeof(T)));
    return ptr;
  }
}
