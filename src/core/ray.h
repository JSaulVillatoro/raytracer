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
    intersectionPoint = glm::vec3(0.0f);
    normal = glm::vec3(0.0f);
    time = std::numeric_limits<double>::infinity();
    Color color = Color();
  }
  
  virtual ~Ray(){};
  void initializeRay(Camera camera, int imageWidth, int imageHeight, int i, int j);
  void initializeRay(glm::vec3 startPoint, glm::vec3 endPoint);
  glm::vec3 getPoint(){ return point; }
  void setPoint(glm::vec3 aPoint){ point = aPoint; };
  glm::vec3 getDirection(){ return direction; }
  void setDirection(glm::vec3 aDirection){direction = aDirection;}
  glm::vec3 getIntersectionPoint(){ return intersectionPoint; }
  float getTime(){ return time; }
  void setTime(float aTime){ time = aTime; intersectionPoint = point + (time * direction);}
  Color getColor(){ return color; }
  void setColor(glm::vec4 newColor){ color.setColor(newColor); }
  glm::vec3 getNormal(){return normal;}
  void setNormal(glm::vec3 aNormal){normal = aNormal;}
  
 private:
  glm::vec3 point;
  glm::vec3 direction;
  glm::vec3 intersectionPoint;
  glm::vec3 normal;
  float time;
  Color color;
};
#endif