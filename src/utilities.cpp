#include <fstream>
#include <array>
#include <cmath>

#include "REDonFDTD/utilities.hpp"

std::array<double,3> REDonFDTD::util::cross(std::array<double,3> array1, std::array<double,3> array2){
  std::array<double,3> array3;
  array3[0] = array1[1]*array2[2] - array1[2]*array2[1];
  array3[1] = array1[2]*array2[0] - array1[0]*array2[2];
  array3[2] = array1[0]*array2[1] - array1[1]*array2[0];

  return array3;
}

double REDonFDTD::util::dot(std::array<double,3> array1, std::array<double,3> array2){
  double dotProduct=0;
  for (size_t i=0; i< array1.size(); ++i)
  {
    dotProduct += array1[i]*array2[i];
  }

  return dotProduct;
}

double REDonFDTD::util::theta(std::array<double,3> array1, std::array<double,3> array2){
  const double cos=dot(array1, array2)/(magnitude(array1)*REDonFDTD::util::magnitude(array2));
  return acos(cos);
}

double REDonFDTD::util::magnitude(std::array<double,3> a){
  const double mag = std::sqrt(dot(a,a));
  return mag;
}

std::array<double,3> REDonFDTD::util::norm(std::array<double,3> a){
  const double aMag = magnitude(a);
  for (size_t i = 0; i < a.size(); ++i){
    a[i] = a[i]/aMag;
  }
  return a;
}
