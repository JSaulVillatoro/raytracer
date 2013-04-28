#ifndef SPHERE_H
#define SPHERE_H

#include <fstream>
#include "../third_party/glm/glm.hpp"
#include "geometry.h"

class Sphere : public Geometry{
 public:
  Sphere(){
    position = glm::vec3(0.0f);
    radius = 0.0f;
  }
  
  Sphere(std::ifstream& fin){
    position = glm::vec3(0.0f);
    radius = 0.0f;
    parse(fin);
  }
  
  virtual void parse(std::ifstream& fin);
  virtual void print();
  virtual float intersect(Ray* ray, float t0, float t1);
  virtual glm::vec3 calculateNormal(Ray* ray);
  glm::vec3 getPosition(){ return position; }
  float getRadius(){ return radius; }
  
 private:
  glm::vec3 position;
  float radius;
};
#endif
