#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <fstream>
#include <../third_party/glm/glm.hpp>
#include "geometry.h"

class Light_Source : public Geometry{
 public:
  Light_Source(){
    position = glm::vec3(0.0f);
  } 
  
  Light_Source(std::ifstream& in){
    position = glm::vec3(0.0f);
    parse(in);
  }
  
  virtual void parse(std::ifstream& in);
  virtual void print();
  
 private:
  glm::vec3 position;
  Color color;
};
#endif
