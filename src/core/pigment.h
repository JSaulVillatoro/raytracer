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
  
 private:
  Color color;
};
#endif
