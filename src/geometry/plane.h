#ifndef PLANE_H
#define PLANE_H

#include <fstream>
#include "../third_party/glm/glm.hpp"
#include "geometry.h"

class Plane : public Geometry{
 public:
  Plane(){
    normal = glm::vec3(0.0f);
    distance = 0.0f;
  }
  
  Plane(std::ifstream& in){
    normal = glm::vec3(0.0f);
    distance = 0.0f;
    parse(in);
  }
  
  virtual void parse(std::ifstream& fin);
  virtual void print();
  
 private: 
  glm::vec3 normal;
  float distance;
};
#endif
