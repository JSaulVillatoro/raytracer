#ifndef PIGMENT_H
#define PIGMENT_H

#include <fstream>
#include "color.h"

class Pigment{
 public:
  Pigment(){
    //color = new Color();
  }
  
  virtual ~Pigment(){};
  void parsePigment(std::ifstream& fin);
  void printPigment();
  Color getColor(){ return color; }
  void setColor(glm::vec4 newColor){color.setColor(newColor);}
  
 private:
  Color color;
};
#endif
