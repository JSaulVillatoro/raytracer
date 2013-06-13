#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "BoundingBox.h"
#include "../core/parser.h"


float BoundingBox::intersect(Ray* ray){
  
  glm::vec3 p = ray->getPoint();
  
  glm::vec3 d = ray->getDirection();
  
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
    return -1.0f;
  }
  
  if((py > maxY && dy > 0.0f) || (py < minY && dy < 0.0f)){
    return -1.0f;
  }  
  
  if((pz > maxZ && dz > 0.0f) || (pz < minZ && dz < 0.0f)){
    return -1.0f;
  }
  
  if(dx == 0.0f){
    if(px <= minX || px >= maxX){
      return -1.0f;
    }
  }
  else{
    t_1 = (minX - px) / dx;
    t_2 = (maxX - px) / dx;

    if(t_2 < t_1){
      float temp = t_1;
      t_1 = t_2;
      t_2 = temp;
    } 
    
    if(tgMin < t_1){ tgMin = t_1; }
    if(tgMax > t_2){ tgMax = t_2; }
  }
  
  
    if(dy == 0.0f){
    if(py <= minY || py >= maxY){
      return -1.0f;
    }
  }
  else{
    t_1 = (minY - py) / dy;
    t_2 = (maxY - py) / dy;

    if(t_2 < t_1){
      float temp = t_1;
      t_1 = t_2;
      t_2 = temp;
    } 
    
    if(tgMin < t_1){ tgMin = t_1; }
    if(tgMax > t_2){ tgMax = t_2; }
  }
  
    if(dz == 0.0f){
    if(pz <= minZ || pz >= maxZ){
      return -1.0f;
    }
  }
  else{
    t_1 = (minZ - pz) / dz;
    t_2 = (maxZ - pz) / dz;

    if(t_2 < t_1){
      float temp = t_1;
      t_1 = t_2;
      t_2 = temp;
    } 
    
    if(tgMin < t_1){ tgMin = t_1; }
    if(tgMax > t_2){ tgMax = t_2; }
  }
  if(tgMin > tgMax) { return -1.0f; }
  if(tgMax < 0.0f) { return -1.0f; }
  else {
    return tgMin;
  }
}

void BoundingBox::changeBoundingBox(glm::mat4 aTransformationMatrix){
  std::vector<glm::vec3> AABBCorners;
  std::vector<glm::vec3> transformedCorners;

  AABBCorners = getCorners();
  /*
    for(int i = 0; i < 8; i++){
    std::cout << "before " <<  i << " < " << AABBCorners[i].x << ", " << AABBCorners[i].y << ", " << AABBCorners[i].z << ">" << std::endl;
  }
  */
  for(int i = 0; i < 8; i++){
    glm::vec4 tempP = glm::vec4(AABBCorners[i], 1.0f);
    tempP = glm::inverse(aTransformationMatrix) * tempP;
    transformedCorners.push_back(glm::vec3(tempP.x, tempP.y, tempP.z));
  }
/*
   for(int i = 0; i < 8; i++){
    std::cout << "after " << i << " < " << transformedCorners[i].x << ", " << transformedCorners[i].y << ", " << transformedCorners[i].z << ">" << std::endl;
  }
  */
  
  float minX = std::numeric_limits<float>::infinity();
  float minY = std::numeric_limits<float>::infinity();
  float minZ = std::numeric_limits<float>::infinity();

  float maxX = -std::numeric_limits<float>::infinity();
  float maxY = -std::numeric_limits<float>::infinity();
  float maxZ = -std::numeric_limits<float>::infinity();
  
  for(int i = 0; i < 8; i++){
    if(transformedCorners[i].x >= maxX){
      maxX = transformedCorners[i].x;
    }
    if(transformedCorners[i].x <= minX){
      minX = transformedCorners[i].x;
    }
    if(transformedCorners[i].y >= maxY){
      maxY = transformedCorners[i].y;
    }
    if(transformedCorners[i].y <= minY){
      minY = transformedCorners[i].y;
    }
    if(transformedCorners[i].z >= maxZ){
      maxZ = transformedCorners[i].z;
    }
    if(transformedCorners[i].z <= minZ){
      minZ = transformedCorners[i].z;
    }   
  }
  
  corner1 = glm::vec3(minX, minY, minZ);
  corner2 = glm::vec3(maxX, maxY, maxZ);
}

std::vector<glm::vec3> BoundingBox::getCorners(){
  std::vector<glm::vec3> toReturn;
  float minX, maxX, minY, maxY, minZ, maxZ;
    
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
    
    toReturn.push_back(glm::vec3(minX, minY, minZ));
    toReturn.push_back(glm::vec3(maxX, minY, minZ));
    toReturn.push_back(glm::vec3(minX, maxY, minZ));
    toReturn.push_back(glm::vec3(minX, minY, maxZ));
    
    toReturn.push_back(glm::vec3(maxX, maxY, maxZ));
    toReturn.push_back(glm::vec3(minX, maxY, maxZ));
    toReturn.push_back(glm::vec3(maxX, minY, maxZ));
    toReturn.push_back(glm::vec3(maxX, maxY, minZ));
    
    return toReturn;
}