#ifndef BOX_H
#define BOX_H

#include <fstream>
#include "../third_party/glm/glm.hpp"
#include "geometry.h"

class Box : public Geometry{
 public:  
  Box(){
    corner1 = glm::vec3(0.0f);
    corner2 = glm::vec3(0.0f);
  }
  
  Box(std::ifstream& in){
    corner1 = glm::vec3(0.0f);
    corner2 = glm::vec3(0.0f);
    parse(in);
  }
  
  virtual void parse(std::ifstream& fin);
  virtual void print();
  virtual void intersect(Ray* ray);
  
 private:   
  glm::vec3 corner1;
  glm::vec3 corner2;
};
#endif
