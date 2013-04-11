#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include "../third_party/glm/glm.hpp"

class Camera{
 public:    
  Camera(){
    location = glm::vec3(0.0f);
    up = glm::vec3(0.0f);
    right = glm::vec3(0.0f);
    look_at = glm::vec3(0.0f);     
  }
  
  virtual ~Camera(){};
  void parseCamera(std::ifstream& fin);
  void printCamera();
  
 private:
  glm::vec3 location;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 look_at;
};
#endif