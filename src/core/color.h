#ifndef COLOR_H
#define COLOR_H

#include <fstream>
#include "../third_party/glm/glm.hpp"

class Color{
 public:   
  Color(){
    color = glm::vec4(0.0f);
  }
  
  virtual ~Color(){};
  void parseColor(std::ifstream& fin);
  void printColor();
  glm::vec4 getColorVector(){ return color; }
  
 private:
  glm::vec4 color;
};
#endif