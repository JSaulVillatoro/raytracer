#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "sphere.h"
#include "../core/parser.h"

void Sphere::parse(std::ifstream& fin){
   char c = fin.get();
  std::string tempString;

  while(c != '{'){
    c = fin.get();
  }
  
  glm::vec3 tempPosition;
  setVector(fin, tempPosition);  
  
  
  while(c != ','){
   c = fin.get(); 
  }
  
  fin >> radius;
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
      //std::cout << translation.x << " " << translation.y << " " << translation.z << std::endl;
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
  //print();
    setTransformationMatrix(glm::translate(glm::mat4(1.0f), tempPosition));

    setBoundingBox();
    
   // std::cout << "bounding box corner 1 x: " << boundingBox.getCorner1().x << " y: " << boundingBox.getCorner1().y << " z: " << boundingBox.getCorner1().z << std::endl;
   // std::cout << "bounding box corner 2 x: " << boundingBox.getCorner2().x << " y: " << boundingBox.getCorner2().y << " z: " << boundingBox.getCorner2().z << std::endl;

  
}

Geometry* Sphere::intersect(Ray* ray, float t0, float t1){
  
  glm::vec3 p = ray->getPoint();
  glm::vec4 tempP = glm::vec4(p, 1.0f);
  tempP = glm::inverse(getTransformationMatrix()) * tempP;
  
  glm::vec3 d = ray->getDirection();
   glm::vec4 tempD = glm::vec4(d, 0.0f);
  tempD = glm::inverse(getTransformationMatrix()) * tempD;
    
  p.x = tempP.x;
  p.y = tempP.y;
  p.z = tempP.z;
    
  d.x = tempD.x;
  d.y = tempD.y;
  d.z = tempD.z;
  
 // p = p - position;
    
  float firstTerm = -1.0f * glm::dot(d, p);
  
  float d_dot_p_squared = glm::dot(d, p);
  d_dot_p_squared *= d_dot_p_squared;
  
  float d_dot_d = glm::dot(d, d);
  float p_dot_p = glm::dot(p, p);
  
  float underRoot = d_dot_p_squared - (d_dot_d * (p_dot_p - (radius * radius)));
  
  if(underRoot < 0.0f){
    return NULL;
  }
  
  float t_one = (firstTerm - sqrt(underRoot)) / d_dot_d;
  float t_two = (firstTerm + sqrt(underRoot)) / d_dot_d;

  
  if(t_one < 0.0f && t_two < 0.0f){
    return NULL;
  }
  
  float pos_t_one = abs(t_one);
  float pos_t_two = abs(t_two);
  
  float theT;
  
  if(pos_t_one <= pos_t_two){
   if(t_one <= 0.0f){
     theT = t_two;
   }
   else{
     theT = t_one;
   }
  }
  
  else{
    if(t_two < 0.0f){
     theT = t_one;
   }
   else{
     theT = t_two;
   }
  }
  
  if(theT > t0 && theT < t1){
    
    glm::vec3 poi = p + theT * d;
    glm::vec4 n_os = glm::vec4(poi - position, 0.0f);
    glm::vec4 n_ws4 = n_os * glm::inverse(getTransformationMatrix());
    
    //glm::vec3 n_ws = glm::vec3(n_ws4.x, n_ws4.y, n_ws4.z); 
    glm::vec3 n_ws = glm::vec3(n_ws4); 

    
    ray->setNormal(n_ws);
    ray->setTime(theT);
    //printf("BODIED\n");
    return this;
  }
  else{
    return NULL;
  }
}

void Sphere::print(){
  std::cout << "=== Sphere ===" << std::endl; 
  std::cout << "position: <" << position.x << ",  " << position.y << ", " << position.z << ">" << std::endl; 
  std::cout << "radius: " << radius << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}

glm::vec3 Sphere::calculateNormal(Ray* ray){
  return ray->getIntersectionPoint() - position;
}

void Sphere::setBoundingBox(){
  glm::vec3 corner1 = position - glm::vec3(radius, radius, radius);
  glm::vec3 corner2 = position + glm::vec3(radius, radius, radius);

  boundingBox.setCorners(corner1, corner2);
  boundingBox.changeBoundingBox(getTransformationMatrix());
  
}
