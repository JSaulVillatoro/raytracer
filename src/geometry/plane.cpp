#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "plane.h"
#include "../core/parser.h"

void Plane::parse(std::ifstream& fin){
  char c = fin.get();
  std::string tempString;
  
    while(c != '{'){
    c = fin.get();  }
  
  setVector(fin, normal);
  
  while(c != ','){
   c = fin.get(); 
  }
  fin >> distance;
  
  fin >> tempString;

  glm::vec3 empty;
  
  while(tempString != "}"){
            if(tempString[0] == '/' && tempString[1] == '/'){
      getline(fin, tempString);
    }
    else{
    if(tempString == "pigment"){
      setPigment(fin);
    }
    else if(tempString == "finish"){
      setFinish(fin);
    }
    else if(tempString == "translate"){
      glm::vec3 translation;
      setVector(fin, translation);
      setTransformationMatrix(glm::translate(glm::mat4(1.0f), translation));
    }
    else if(tempString == "rotate"){
      glm::vec3 rotate;
      setVector(fin, rotate);
      
      if(rotate.x != 0.0f){
	setTransformationMatrix(glm::rotate(glm::mat4(1.0f), rotate.x, glm::vec3(1.0f, 0.0f, 0.0f)));
      }
      else if(rotate.y != 0.0f){
	setTransformationMatrix(glm::rotate(glm::mat4(1.0f), rotate.y, glm::vec3(0.0f, 1.0f, 0.0f)));
      }
      else{
	setTransformationMatrix(glm::rotate(glm::mat4(1.0f), rotate.z, glm::vec3(0.0f, 0.0f, 1.0f)));
      }
    }
    else if(tempString == "scale"){
      glm::vec3 scale;
      setVector(fin, scale);
      setTransformationMatrix(glm::scale(glm::mat4(1.0f), scale));
    }
    else{
      std::cout << "Unidentified keyword: " << tempString << std::endl;
      exit(0);
    }
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

float Plane::intersect(Ray* ray, float t0, float t1){
  
  glm::vec3 p0 = ray->getPoint();
  glm::vec4 tempP = glm::vec4(p0, 1.0f);
  tempP = glm::inverse(getTransformationMatrix()) * tempP;
  
  glm::vec3 d = ray->getDirection();
  glm::vec4 tempD = glm::vec4(d, 0.0f);
  tempD = glm::inverse(getTransformationMatrix()) * tempD;
    
  p0.x = tempP.x;
  p0.y = tempP.y;
  p0.z = tempP.z;
    
  d.x = tempD.x;
  d.y = tempD.y;
  d.z = tempD.z;
  
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
    return -1.0f;
  }  
  glm::vec3 diff_p = p - p0;
  
  float t = glm::dot(diff_p, normal) / glm::dot(d, normal);
  
  if( t > t0 && t < t1){
    glm::vec4 normal4 = glm::vec4(normal, 0.0);
    normal4 = normal4 * glm::inverse(getTransformationMatrix());
    glm::vec3 n_ws = glm::vec3(normal4.x, normal4.y, normal4.z);
    ray->setNormal(n_ws);
    return t;
  }
  else{
    return -1.0f;
  }
}


glm::vec3 Plane::calculateNormal(Ray* ray){
   return normal;
 }
