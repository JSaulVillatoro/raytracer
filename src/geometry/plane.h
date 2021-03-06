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
  virtual Geometry* intersect(Ray* ray, float t0, float t1);
  virtual glm::vec3 calculateNormal(Ray* ray);
  virtual void setBoundingBox();

  
 private: 
  glm::vec3 normal;
  float distance;
};
#endif
