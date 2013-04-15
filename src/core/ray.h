#ifndef RAY_H
#define RAY_H

#include "../third_party/glm/glm.hpp"
#include "camera.h"
#include "color.h"
#include <limits>

class Ray{
 public:    
  Ray(){
    point = glm::vec3(0.0f);
    direction = glm::vec3(0.0f);
    time = std::numeric_limits<double>::infinity();
  }
  
  virtual ~Ray(){};
  void initializeRay(Camera camera, int imageWidth, int imageHeight, int i, int j);
  glm::vec3 getPoint(){ return point; }
  glm::vec3 getDirection(){ return direction; }
  float getTime(){ return time; }
  void setTime(float aTime){ time = aTime; }
  Color getColor(){ return color; }
  void setColor(Color aColor){ color = aColor; }
  
 private:
  glm::vec3 point;
  glm::vec3 direction;
  float time;
  Color color;
};
#endif