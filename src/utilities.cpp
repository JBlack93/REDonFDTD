#include <fstream>
#include <vector>
#include <cmath>

#include "REDonFDTD/utilities.hpp"

std::vector<double> REDonFDTD::util::cross(std::vector<double> vector1, std::vector<double> vector2){
  std::vector<double> vector3 (3);
  vector3[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1];
  vector3[1] = vector1[2]*vector2[0] - vector1[0]*vector2[2];
  vector3[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0];

  return vector3;
}

double REDonFDTD::util::dot(std::vector<double> vector1, std::vector<double> vector2){
  float dotProduct=0;
  for (size_t i=0; i< vector1.size(); ++i)
  {
    dotProduct += vector1[i]*vector2[i];
  }

  return dotProduct;
}

double REDonFDTD::util::magnitude(std::vector<double> a){
  float mag;
  mag = std::sqrt(dot(a,a));
  return mag;
}

std::vector<double> REDonFDTD::util::norm(std::vector<double> a){
  float aMag = magnitude(a);
  for (size_t i = 0; i < a.size(); ++i){
    a[i] = a[i]/aMag;
  }
  return a;
}
