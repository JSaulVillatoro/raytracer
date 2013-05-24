#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <fstream>
#include "../third_party/glm/glm.hpp"
#include "../core/ray.h"
#include <vector>

class BoundingBox{
 public:  
  BoundingBox(){
    corner1 = glm::vec3(0.0f);
    corner2 = glm::vec3(0.0f);
  }
  
  BoundingBox(glm::vec3 corner1, glm::vec3 corner2){
    this->corner1 = corner1;
    this->corner2 = corner2;
  }
  float intersect(Ray* ray);
  void changeBoundingBox(glm::mat4 aTransformationMatrix);
  void setCorners(glm::vec3 corner1, glm::vec3 corner2){
    this->corner1 = corner1;
    this->corner2 = corner2;
  }
  
  glm::vec3 getCorner1(){ return corner1;}
  glm::vec3 getCorner2(){ return corner2;}
  std::vector<glm::vec3> getCorners();
 private:   
  glm::vec3 corner1;
  glm::vec3 corner2;
};
#endif