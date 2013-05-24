#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cone.h"
#include "../core/parser.h"

void Cone::parse(std::ifstream& fin){
     char c = fin.get();
  std::string tempString;

  while(c != '{'){
    c = fin.get();
  }
  
  setVector(fin, base_point);  
  
  
  while(c != ','){
   c = fin.get(); 
  }
  
  fin >> base_radius;
    
    while(c != ','){
   c = fin.get(); 
  }
  
  setVector(fin, cap_point);
    
  while(c != ','){
    c = fin.get();
  }
      //c = fin.get();
     // std::cout << c << std::endl;

  fin >> tempString;
       
  fin >> cap_radius;  
  
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
}

void Cone::print(){
  std::cout << "=== Cone ===" << std::endl; 
  std::cout << "Base Point: <" << base_point.x << ",  " << base_point.y << ", " << base_point.z << ">" << std::endl; 
  std::cout << "Base Radius: " << base_radius << std::endl;
  std::cout << "Cap Point: <" << cap_point.x << ",  " << cap_point.y << ", " << cap_point.z << ">" << std::endl; 
  std::cout << "Cap Radius: " << cap_radius << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}

Geometry* Cone::intersect(Ray* ray, float t0, float t1){return NULL;}
glm::vec3 Cone::calculateNormal(Ray* ray){return glm::vec3(0.0f);}
void Cone::setBoundingBox(){}
