#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <fstream>
#include "../core/pigment.h"
#include "../core/finish.h"
#include "../core/ray.h"
#include <../third_party/glm/glm.hpp>

class Light_Source{
 public:
  Light_Source(){
    position = glm::vec3(0.0f);
  } 
  
  Light_Source(std::ifstream& in){
    position = glm::vec3(0.0f);
    parse(in);
  }
  
  void parse(std::ifstream& in);
  void print();
  void intersect(Ray* ray);
  glm::vec3 getPosition(){ return position; }
  Color getColor(){ return color;}
  
 private:
  glm::vec3 position;
  Color color;
};
#endif
