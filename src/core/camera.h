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
  glm::vec3 getLocation(){return location;}
  glm::vec3 getUp(){return up;}
  glm::vec3 getRight(){return right;}
  glm::vec3 getLookAt(){return look_at;}

 private:
  glm::vec3 location;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 look_at;
};
#endif