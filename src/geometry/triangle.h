#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <fstream>
#include "../third_party/glm/glm.hpp"
#include "geometry.h"

class Triangle : public Geometry{
 public:   
  Triangle(){
    corner1 = glm::vec3(0.0f);
    corner2 = glm::vec3(0.0f);
    corner3 = glm::vec3(0.0f);
  }
  
  Triangle(std::ifstream& in){
    corner1 = glm::vec3(0.0f);
    corner2 = glm::vec3(0.0f);
    corner3 = glm::vec3(0.0f);
    parse(in);
  }
  
  virtual void parse(std::ifstream& fin);
  virtual void print();
  virtual void intersect(Ray* ray);
  
 private:   
  glm::vec3 corner1;
  glm::vec3 corner2;
  glm::vec3 corner3; 
};
#endif
