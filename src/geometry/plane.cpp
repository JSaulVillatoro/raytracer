#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "plane.h"
#include "../core/parser.h"

void Plane::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, normal);
  fin >> distance;
  
  fin >> tempString;

  glm::vec3 empty;
  
  while(tempString != "}"){
    if(tempString == "pigment"){
      setPigment(fin);
    }
    else if(tempString == "finish"){
      setFinish(fin);
    }
    else if(tempString == "translate"){
      setVector(fin, empty);
    }
    else if(tempString == "rotate"){
      setVector(fin, empty);
    }
    else if(tempString == "scale"){
      setVector(fin, empty);
    }
    else{
      std::cout << "Unidentified keyword: " << tempString << std::endl;
      exit(0);
    }
    
    fin >> tempString; 
  }	
}

void Plane::print(){
  std::cout << "=== Plane ===" << std::endl; 
  std::cout << "normal: <" << normal.x << ",  " << normal.y << ", " << normal.z << ">" << std::endl; 
  std::cout << "distance: " << distance << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;  
}
void Plane::intersect(Ray* ray){
  glm::vec3 normalized_normal = glm::normalize(normal);
  
  glm::vec3 p;
  
  if(normalized_normal.x != 0.0f){
    float x = distance / normalized_normal.x; 
    p = glm::vec3(x, 0.0f, 0.0f);
  }
  else if(normalized_normal.y != 0.0f){
    float y = distance / normalized_normal.y; 
    p = glm::vec3(0.0f, y, 0.0f);  
  }
  else if(normalized_normal.z != 0.0f){
    float z = distance / normalized_normal.z; 
    p = glm::vec3(0.0f, 0.0f, z);  
  }
  else{
    return;
  }  
  glm::vec3 diff_p = p - ray->getPoint();
  
  float t = glm::dot(diff_p, normal) / glm::dot(ray->getDirection(), normal);
  
  if( t > 0 && t < ray->getTime()){
    ray->setTime(t);
    ray->setColor(getPigment().getColor());
  }
}