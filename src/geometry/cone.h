#ifndef CONE_H
#define CONE_H

#include <fstream>
#include "../third_party/glm/glm.hpp"
#include "geometry.h"

class Cone : public Geometry{
 public:
  Cone(){
    base_point = glm::vec3(0.0f);
    cap_point = glm::vec3(0.0f);
    base_radius = 0.0f;
    cap_radius = 0.0f;
  }
  
  Cone(std::ifstream& in){
    base_point = glm::vec3(0.0f);
    cap_point = glm::vec3(0.0f);
    base_radius = 0.0f;
    cap_radius = 0.0f;
    parse(in);
  }
  
  virtual void parse(std::ifstream& fin);
  virtual void print();
  virtual float intersect(Ray* ray, float t0, float t1);
  virtual glm::vec3 calculateNormal(Ray* ray);


  
 private:   
  glm::vec3 base_point;
  glm::vec3 cap_point;
  float base_radius;
  float cap_radius;
};
#endif
