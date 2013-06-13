#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <fstream>
#include <vector>
#include "../core/pigment.h"
#include "../core/finish.h"
#include "../core/ray.h"
#include "light_source.h"
#include "BoundingBox.h"
#include "../third_party/glm/gtc/matrix_transform.hpp"

class Geometry{
 public:  
  Geometry(){}
  
  virtual ~Geometry(){};
  virtual void parse(std::ifstream& fin) = 0;
  virtual void print() = 0;
  virtual Geometry* intersect(Ray* ray, float t0, float t1) = 0;
  virtual glm::vec3 calculateNormal(Ray* ray) = 0;
  virtual void setBoundingBox() = 0;
  
  void setPigment(std::ifstream& fin){ pigment.parsePigment(fin); }
  void setFinish(std::ifstream& fin){ finish.parseFinish(fin); }
  Pigment getPigment(){ return pigment; }
  Finish getFinish(){ return finish; }
  glm::mat4 getTransformationMatrix(){return transformationMatrix;}
  void setTransformationMatrix(glm::mat4 aMatrix){transformationMatrix = aMatrix;}
  void setITM(glm::mat4 aMatrix){ ITM = glm::inverse(aMatrix); }
  glm::mat4 getITM(){ return ITM; }
  BoundingBox getBoundingBox(){ return boundingBox;}
  glm::vec3 getCenter(){ 
    
    float centerX;
    float centerY;
    float centerZ;
    
    centerX = (boundingBox.getCorner1().x + boundingBox.getCorner2().x) / 2.0f;
    centerY = (boundingBox.getCorner1().y + boundingBox.getCorner2().y) / 2.0f;
    centerZ = (boundingBox.getCorner1().z + boundingBox.getCorner2().z) / 2.0f;

    return glm::vec3(centerX, centerY, centerZ);
  }
    BoundingBox boundingBox;
      glm::vec3 velocity;

  
 private:
  Pigment pigment;
  Finish finish;
  glm::mat4 transformationMatrix;
  glm::mat4 ITM;
};
#endif
