#ifndef COLOR_H
#define COLOR_H

#include <fstream>
#include "../third_party/glm/glm.hpp"

class Color{
 public:   
  Color(){
    color = glm::vec4(0.0f);
  }
  
  Color(glm::vec4 aColor){
    color = aColor;
  }
  
  virtual ~Color(){};
  void parseColor(std::ifstream& fin);
  void printColor();
  glm::vec4 getColorVector(){ return color; }
  void setColor(glm::vec4 newColor){color = newColor;}
  
 private:
  glm::vec4 color;
};
#endif