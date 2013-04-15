#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "sphere.h"
#include "../core/parser.h"

void Sphere::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, position);
  
  fin >> radius;
  //pesky comma
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

void Sphere::print(){
  std::cout << "=== Sphere ===" << std::endl; 
  std::cout << "position: <" << position.x << ",  " << position.y << ", " << position.z << ">" << std::endl; 
  std::cout << "radius: " << radius << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}

void Sphere::intersect(Ray* ray){
  
  glm::vec3 p = ray->getPoint() - position;
  glm::vec3 d = ray->getDirection();
    
  float firstTerm = -1.0f * glm::dot(d, p);
  
  float d_dot_p_squared = glm::dot(d, p);
  d_dot_p_squared *= d_dot_p_squared;
  
  float d_dot_d = glm::dot(d, d);
  float p_dot_p = glm::dot(p, p);
  
  float underRoot = d_dot_p_squared - (d_dot_d * (p_dot_p - (radius * radius)));
  
  if(underRoot < 0.0f){
    return;
  }
  
  float t_one = (firstTerm - sqrt(underRoot)) / d_dot_d;
  float t_two = (firstTerm + sqrt(underRoot)) / d_dot_d;

  
  if(t_one < 0.0f && t_two < 0.0f){
    return;
  }
  
  float pos_t_one = abs(t_one);
  float pos_t_two = abs(t_two);
  
  float theT;
  
  if(pos_t_one <= pos_t_two){
   if(t_one < 0.0f){
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
  
  if(theT < ray->getTime()){
    ray->setTime(theT);
    ray->setColor(getPigment().getColor());
  }
}