#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "triangle.h"
#include "../core/parser.h"

void Triangle::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, corner1);
  setVector(fin, corner2);
  setVector(fin, corner3);    
  
  fin >> tempString;

  glm::mat4 tempTransformationMatrix = glm::mat4(1.0f);
  
  while(tempString != "}"){
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
    else{
      std::cout << "Unidentified keyword: " << tempString << std::endl;
      exit(0);
    }
    
    fin >> tempString;  
  }	
 // print();
  setTransformationMatrix(tempTransformationMatrix);
  setITM(tempTransformationMatrix);
  setBoundingBox();
}

void Triangle::print(){
  std::cout << "=== Triangle ===" << std::endl; 
  std::cout << "Corner 1: <" << corner1.x << ",  " << corner1.y << ", " << corner1.z << ">" << std::endl;
  std::cout << "Corner 2: <" << corner2.x << ",  " << corner2.y << ", " << corner2.z << ">" << std::endl;
  std::cout << "Corner 3: <" << corner3.x << ",  " << corner3.y << ", " << corner3.z << ">" << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}

Geometry* Triangle::intersect(Ray* ray, float t0, float t1){
  
    
  glm::vec3 p = ray->getPoint();
  glm::vec4 tempP = glm::vec4(p, 1.0f);
  tempP = getITM() * tempP;
  
  glm::vec3 d = ray->getDirection();
   glm::vec4 tempD = glm::vec4(d, 0.0f);
  tempD = getITM() * tempD;
    
  p.x = tempP.x;
  p.y = tempP.y;
  p.z = tempP.z;
    
  d.x = tempD.x;
  d.y = tempD.y;
  d.z = tempD.z;
  
  glm::mat3 A = glm::mat3( (corner1.x - corner2.x), (corner1.y - corner2.y), (corner1.z - corner2.z),
		        (corner1.x - corner3.x), (corner1.y - corner3.y), (corner1.z - corner3.z),
		       (d.x), (d.y), (d.z)
  );
  
  glm::vec3 b = glm::vec3((corner1.x - p.x), (corner1.y - p.y), (corner1.z - p.z));
  
  glm::mat3 inverseA = glm::inverse(A);
  
  glm::vec3 solutions = inverseA * b;
  
  if(solutions.z < t0 || solutions.z > t1){
    return NULL;
  }
  
  else if(solutions.y > 1.0f || solutions.y < 0.0f){
    return NULL;
  }
  
  else if(solutions.x > 1.0f || solutions.x < 0.0f){
    return NULL;
  }
  else if(solutions.x + solutions.y >= 1.0f){
    return NULL;
  }
  else{
   
    
  glm::vec3 ray1 = corner2 - corner1;
  glm::vec3 ray2 = corner3 - corner1;
  
  glm::vec3 toReturn = glm::cross(ray1, ray2);
  
      glm::vec4 normal4 = glm::vec4(toReturn, 0.0f);
    normal4 = normal4 * getITM();
    glm::vec3 n_ws = glm::vec3(normal4.x, normal4.y, normal4.z);
    
    //std::cout << "x: " << normal4.x << " y: " << normal4.y << " z: " << normal4.z << std::endl;
    ray->setNormal(n_ws);
  ray->setTime(solutions.z);
    return this;
  }
}
glm::vec3 Triangle::calculateNormal(Ray* ray){
  glm::vec3 ray1 = corner2 - corner1;
  glm::vec3 ray2 = corner3 - corner1;
  
  glm::vec3 toReturn = glm::cross(ray1, ray2);
  
  //std::cout << "x: " << toReturn.x << " y: " << toReturn.y << " z: " << toReturn.z << std::endl;
  
  return  glm::cross(ray1, ray2);
  
}

void Triangle::setBoundingBox(){
  
    std::vector<glm::vec3> myCorners;

    myCorners.push_back(corner1);
    myCorners.push_back(corner2);
    myCorners.push_back(corner3);
  
  float minX = std::numeric_limits<float>::infinity();
  float minY = std::numeric_limits<float>::infinity();
  float minZ = std::numeric_limits<float>::infinity();

  float maxX = -std::numeric_limits<float>::infinity();
  float maxY = -std::numeric_limits<float>::infinity();
  float maxZ = -std::numeric_limits<float>::infinity();
	
	for(int i = 0; i < 3; i++){
	  if(myCorners[i].x < minX){
	    minX = myCorners[i].x;
	  }
	  if(myCorners[i].x > maxX){
	    maxX = myCorners[i].x;
	  }
	  if(myCorners[i].y < minY){
	    minY = myCorners[i].y;
	  }
	  if(myCorners[i].y > maxY){
	    maxY = myCorners[i].y;
	  }
	  if(myCorners[i].z < minZ){
	    minZ = myCorners[i].z;
	  }
	  if(myCorners[i].z > maxZ){
	    maxZ = myCorners[i].z;
	  }
	}

  
  glm::vec3 cornerA = glm::vec3(minX, minY, minZ);
  
  glm::vec3 cornerB = glm::vec3(maxX, maxY, maxZ);
 
  
  boundingBox.setCorners(cornerA, cornerB);
  boundingBox.changeBoundingBox(getITM());
  
}