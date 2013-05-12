#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include "../third_party/glm/glm.hpp"
#include "camera.h"
#include "ray.h"

void Ray::initializeRay(Camera camera, int imageWidth, int imageHeight, int i, int j){
  
  point = camera.getLocation();
  
  
  float rightLength = sqrt(((camera.getRight().x)*(camera.getRight().x)) + ((camera.getRight().y)*(camera.getRight().y)) + ((camera.getRight().z)*(camera.getRight().z)));
  float l = (rightLength * -1.0f) / 2.0f;
 
  float upLength = sqrt(((camera.getUp().x)*(camera.getUp().x)) + ((camera.getUp().y)*(camera.getUp().y)) +      ((camera.getUp().z)*(camera.getUp().z)));
  float b = (upLength * -1.0f) / 2.0f;  
  
  
  float r = -1.0f * l;
  float t = -1.0f * b;
  
  glm::vec3 u = camera.getRight();
  glm::vec3 v = camera.getUp();
  glm::vec3 w = glm::cross(u, v);
  
  float u_s = l + (r - l) * ((i + 0.5f) / imageWidth);
  float v_s = b + (t - b) * ((j + 0.5f) / imageHeight);
  float w_s = -1.0f;
  
  glm::vec3 u_term = u_s * glm::normalize(u);
  glm::vec3 v_term = v_s * glm::normalize(v);
  glm::vec3 w_term = w_s * glm::normalize(w);
  
  direction = u_term + v_term + w_term;
  
  //glm::vec3 temp = camera.getLocation() + u_term + v_term + w_term;
  //direction = temp - camera.getLocation();
  //std::cout << "x: " << direction.x << " y: " << direction.y << " z: " <<direction.z << std::endl;
}

void Ray::initializeRay(glm::vec3 startPoint, glm::vec3 endPoint){
  direction = endPoint - startPoint;
  point = startPoint + 0.00001f * direction;
  setTime(1.0f);
}
