#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <fstream>
#include <vector>
#include "../core/pigment.h"
#include "../core/finish.h"
#include "../core/ray.h"
#include "light_source.h"
#include "../third_party/glm/gtc/matrix_transform.hpp"

class Geometry{
 public:  
  Geometry(){}
  
  virtual ~Geometry(){};
  virtual void parse(std::ifstream& fin) = 0;
  virtual void print() = 0;
  virtual float intersect(Ray* ray, float t0, float t1) = 0;
  virtual glm::vec3 calculateNormal(Ray* ray) = 0;
  
  void setPigment(std::ifstream& fin){ pigment.parsePigment(fin); }
  void setFinish(std::ifstream& fin){ finish.parseFinish(fin); }
  Pigment getPigment(){ return pigment; }
  Finish getFinish(){ return finish; }
  glm::mat4 getTransformationMatrix(){return transformationMatrix;}
  void setTransformationMatrix(glm::mat4 aMatrix){transformationMatrix = aMatrix * transformationMatrix;} 
  
 private:
  Pigment pigment;
  Finish finish;
  glm::mat4 transformationMatrix;
};
#endif
