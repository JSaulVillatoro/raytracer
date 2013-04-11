#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <fstream>
#include "../core/pigment.h"
#include "../core/finish.h"

class Geometry{
 public:  
  Geometry(){}
  
  virtual ~Geometry(){};
  virtual void parse(std::ifstream& fin) = 0;
  virtual void print() = 0;
  
  void setPigment(std::ifstream& fin){ pigment.parsePigment(fin); }
  void setFinish(std::ifstream& fin){ finish.parseFinish(fin); }
  Pigment getPigment(){ return pigment; }
  Finish getFinish(){ return finish; }
  
 private:
  Pigment pigment;
  Finish finish;
};
#endif
