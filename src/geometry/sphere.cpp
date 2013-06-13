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
  
  glm::mat4 tempTransformationMatrix = glm::mat4(1.0f);
  
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
      tempTransformationMatrix = glm::translate(glm::mat4(1.0f), translation) * tempTransformationMatrix;
    }
    else if(tempString == "rotate"){
      glm::vec3 rotate;
      setVector(fin, rotate);
      
      if(rotate.x != 0.0f){
	tempTransformationMatrix = glm::rotate(glm::mat4(1.0f), rotate.x, glm::vec3(1.0f, 0.0f, 0.0f)) * tempTransformationMatrix;
      }
      else if(rotate.y != 0.0f){
	tempTransformationMatrix = glm::rotate(glm::mat4(1.0f), rotate.y, glm::vec3(0.0f, 1.0f, 0.0f)) * tempTransformationMatrix;
      }
      else{
	tempTransformationMatrix = glm::rotate(glm::mat4(1.0f), rotate.z, glm::vec3(0.0f, 0.0f, 1.0f)) * tempTransformationMatrix;
      }
    }
    else if(tempString == "scale"){
      glm::vec3 scale;
      setVector(fin, scale);
      tempTransformationMatrix = glm::scale(glm::mat4(1.0f), scale) * tempTransformationMatrix;
    }
    
    else if(tempString == "velocity"){
      setVector(fin, velocity);
    }
    else{
      std::cout << "Unidentified keyword: " << tempString << std::endl;
      exit(0);
    }
    }
    
    fin >> tempString;  
  }	
    tempTransformationMatrix = glm::translate(glm::mat4(1.0f), tempPosition) * tempTransformationMatrix;  
    setTransformationMatrix(tempTransformationMatrix);
    setITM(tempTransformationMatrix);
    setBoundingBox();
}

Geometry* Sphere::intersect(Ray* ray, float t0, float t1){

  float ttime = (float)rand() / (float) RAND_MAX;
  
  glm::vec3 amountMove = velocity * ttime;
  
  glm::mat4 tempITMatrix = glm::translate(glm::mat4(1.0f), amountMove) * getTransformationMatrix();
  tempITMatrix = glm::inverse(tempITMatrix);
  
  glm::vec3 p = ray->getPoint();
  glm::vec4 tempP = glm::vec4(p, 1.0f);
  tempP = tempITMatrix * tempP;
  
  glm::vec3 d = ray->getDirection();
   glm::vec4 tempD = glm::vec4(d, 0.0f);
  tempD = tempITMatrix * tempD;
    
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
    glm::vec4 n_ws4 = n_os * tempITMatrix;
    
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
  glm::vec3 initCorner1 = position - glm::vec3(radius, radius, radius);
  glm::vec3 initCorner2 = position + glm::vec3(radius, radius, radius);
  
  glm::vec3 finalCorner1 = (position + velocity) - glm::vec3(radius, radius, radius);
  glm::vec3 finalCorner2 = (position + velocity) + glm::vec3(radius, radius, radius);

  
  std::vector<glm::vec3> corners;
  
  corners.push_back(initCorner1);
  corners.push_back(initCorner2);
  corners.push_back(finalCorner1);
  corners.push_back(finalCorner2);
  
  float minX = std::numeric_limits<float>::infinity();
  float minY = std::numeric_limits<float>::infinity();
  float minZ = std::numeric_limits<float>::infinity();

  float maxX = -std::numeric_limits<float>::infinity();
  float maxY = -std::numeric_limits<float>::infinity();
  float maxZ = -std::numeric_limits<float>::infinity();
  
  for(int i = 0; i < 4; i++){
     if(corners[i].x >= maxX){
      maxX = corners[i].x;
    }
    if(corners[i].x <= minX){
      minX = corners[i].x;
    }
    if(corners[i].y >= maxY){
      maxY = corners[i].y;
    }
    if(corners[i].y <= minY){
      minY = corners[i].y;
    }
    if(corners[i].z >= maxZ){
      maxZ = corners[i].z;
    }
    if(corners[i].z <= minZ){
      minZ = corners[i].z;
    }   
  }
  
  glm::vec3 corner1 = glm::vec3(minX, minY, minZ);
  glm::vec3 corner2 = glm::vec3(maxX, maxY, maxZ);

 
  boundingBox.setCorners(corner1, corner2);
  boundingBox.changeBoundingBox(getITM());
  
}

