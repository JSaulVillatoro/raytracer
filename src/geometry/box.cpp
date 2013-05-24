#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "box.h"
#include "../core/parser.h"

void Box::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, corner1);
  setVector(fin, corner2);
   
  fin >> tempString;

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
      std::cout << "Unidentified keyword : " << tempString << std::endl;
      exit(0);
    }
    fin >> tempString;
  }
  setBoundingBox();
  //std::cout << "bounding box corner 1 x: " << boundingBox.getCorner1().x << " y: " << boundingBox.getCorner1().y << " z: " << boundingBox.getCorner1().z << std::endl;
  //std::cout << "bounding box corner 2 x: " << boundingBox.getCorner2().x << " y: " << boundingBox.getCorner2().y << " z: " << boundingBox.getCorner2().z << std::endl;
}

void Box::print(){
  std::cout << "=== Box ===" << std::endl; 
  std::cout << "Corner 1: <" << corner1.x << ",  " << corner1.y << ", " << corner1.z << ">" << std::endl; 
  std::cout << "Corner 2: <" << corner2.x << ",  " << corner2.y << ", " << corner2.z << ">" << std::endl; 
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}

Geometry* Box::intersect(Ray* ray, float t0, float t1){
  enum aPlane {left, right, top, bottom, near, far };
  
  enum aPlane thePlane;
  enum aPlane tempPlane;
  
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
  
  float minX, maxX, minY, maxY, minZ, maxZ;
  
  float px = p.x;
  float py = p.y;
  float pz = p.z;
  
  float dx = d.x;
  float dy = d.y;
  float dz = d.z;
  
  float t_1, t_2;
  
  float tgMin = -std::numeric_limits<float>::infinity();
  float tgMax = std::numeric_limits<float>::infinity();
  
  if(corner1.x < corner2.x){
    minX = corner1.x;
    maxX = corner2.x;
  }
  else{
    minX = corner2.x;
    maxX = corner1.x;
  }
  
  if(corner1.y < corner2.y){
    minY = corner1.y;
    maxY = corner2.y;
  }
  else{
    minY = corner2.y;
    maxY = corner1.y;
  }
  
  if(corner1.z < corner2.z){
    minZ = corner1.z;
    maxZ = corner2.z;
  }
  else{
    minZ = corner2.z;
    maxZ = corner1.z;
  }
  
  if((px > maxX && dx > 0.0f) || (px < minX && dx < 0.0f)){
    return NULL;
  }
  
  if((py > maxY && dy > 0.0f) || (py < minY && dy < 0.0f)){
    return NULL;
  }  
  
  if((pz > maxZ && dz > 0.0f) || (pz < minZ && dz < 0.0f)){
    return NULL;
  }
  
  if(dx == 0.0f){
    if(px <= minX || px >= maxX){
      return NULL;
    }
  }
  else{
    t_1 = (minX - px) / dx;
    t_2 = (maxX - px) / dx;

    if(t_2 < t_1){
      float temp = t_1;
      t_1 = t_2;
      t_2 = temp;
      tempPlane = right;
    } 
    else{
      tempPlane = left;
    }
    
    if(tgMin < t_1){ tgMin = t_1; thePlane = tempPlane;}
    if(tgMax > t_2){ tgMax = t_2; }
  }
  
  
    if(dy == 0.0f){
    if(py <= minY || py >= maxY){
      return NULL;
    }
  }
  else{
    t_1 = (minY - py) / dy;
    t_2 = (maxY - py) / dy;

    if(t_2 < t_1){
      float temp = t_1;
      t_1 = t_2;
      t_2 = temp;
      tempPlane = top;
    } 
    else{
      tempPlane = bottom;
    }
    
    if(tgMin < t_1){ tgMin = t_1; thePlane = tempPlane;}
    if(tgMax > t_2){ tgMax = t_2; }
  }
  
    if(dz == 0.0f){
    if(pz <= minZ || pz >= maxZ){
      return NULL;
    }
  }
  else{
    t_1 = (minZ - pz) / dz;
    t_2 = (maxZ - pz) / dz;

    if(t_2 < t_1){
      float temp = t_1;
      t_1 = t_2;
      t_2 = temp;
      tempPlane = far;
    } 
    else{
      tempPlane = near;
    }
    
    if(tgMin < t_1){ tgMin = t_1; thePlane = tempPlane;}
    if(tgMax > t_2){ tgMax = t_2; }
  }
  if(tgMin > tgMax) { return NULL; }
  if(tgMax < 0.0f) { return NULL; }
  
  
    if(tgMin > t0 && tgMin < t1){
     glm::vec3 poi = p + tgMin * d;

     if(thePlane == left){
       glm::vec4 n_ws4 = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f) * glm::inverse(getTransformationMatrix());
       glm::vec3 n_ws = glm::vec3(n_ws4); 
           //   std::cout<< "left: " << n_ws.x << ", " << n_ws.y << ", " << n_ws.z << std::endl;

       ray->setNormal(n_ws);
     }
     else if(thePlane == right){       
       glm::vec4 n_ws4 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * glm::inverse(getTransformationMatrix());
       glm::vec3 n_ws = glm::vec3(n_ws4); 
            //  std::cout<< "right: " << n_ws.x << ", " << n_ws.y << ", " << n_ws.z << std::endl;

       ray->setNormal(n_ws);
     }
     else if(thePlane == bottom){
       glm::vec4 n_ws4 = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f) * glm::inverse(getTransformationMatrix());
       glm::vec3 n_ws = glm::vec3(n_ws4.x, n_ws4.y, n_ws4.z); 
            //  std::cout<< "bottom: " << n_ws.x << ", " << n_ws.y << ", " << n_ws.z << std::endl;

       ray->setNormal(n_ws);
     }
     else if(thePlane == top){
       glm::vec4 n_ws4 = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) * glm::inverse(getTransformationMatrix());
       glm::vec3 n_ws = glm::vec3(n_ws4); 
           //   std::cout<< "top: " << n_ws.x << ", " << n_ws.y << ", " << n_ws.z << std::endl;

       ray->setNormal(n_ws);
     }
     else if(thePlane == far){
       glm::vec4 n_ws4 = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) * glm::inverse(getTransformationMatrix());
       glm::vec3 n_ws = glm::vec3(n_ws4);
           //   std::cout<< "far: " << n_ws.x << ", " << n_ws.y << ", " << n_ws.z << std::endl;
       ray->setNormal(n_ws);
     }
     else if(thePlane == near){
       glm::vec4 n_ws4 = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f) * glm::inverse(getTransformationMatrix());
       glm::vec3 n_ws = glm::vec3(n_ws4);
             // std::cout<< "near: " << n_ws.x << ", " << n_ws.y << ", " << n_ws.z << std::endl;
       ray->setNormal(n_ws);
     }
     else{
     }
      ray->setTime(tgMin);

      return this;
  
    }
    
      else{
    return NULL;
  }
}
glm::vec3 Box::calculateNormal(Ray* ray){return glm::vec3(1.0f);}
void Box::setBoundingBox(){
   std::vector<glm::vec3> myCorners;

    myCorners.push_back(corner1);
    myCorners.push_back(corner2);
  
  float minX = std::numeric_limits<float>::infinity();
  float minY = std::numeric_limits<float>::infinity();
  float minZ = std::numeric_limits<float>::infinity();

  float maxX = -std::numeric_limits<float>::infinity();
  float maxY = -std::numeric_limits<float>::infinity();
  float maxZ = -std::numeric_limits<float>::infinity();
	
	for(int i = 0; i < 2; i++){
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
  boundingBox.changeBoundingBox(getTransformationMatrix());
}