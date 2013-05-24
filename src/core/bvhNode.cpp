#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "bvhNode.h"
#include "../core/parser.h"

BoundingBox combineBoundingBox(BoundingBox B1, BoundingBox B2){
  std::vector<glm::vec3> temp;
  temp.push_back(B1.getCorner1());
  temp.push_back(B1.getCorner2());
  temp.push_back(B2.getCorner1());
  temp.push_back(B2.getCorner2());
  
  float minX = std::numeric_limits<float>::infinity();
  float minY = std::numeric_limits<float>::infinity();
  float minZ = std::numeric_limits<float>::infinity();

  float maxX = -std::numeric_limits<float>::infinity();
  float maxY = -std::numeric_limits<float>::infinity();
  float maxZ = -std::numeric_limits<float>::infinity();
	
	for(int i = 0; i < 4; i++){
	  if(temp[i].x < minX){
	    minX = temp[i].x;
	  }
	  if(temp[i].x > maxX){
	    maxX = temp[i].x;
	  }
	  if(temp[i].y < minY){
	    minY = temp[i].y;
	  }
	  if(temp[i].y > maxY){
	    maxY = temp[i].y;
	  }
	  if(temp[i].z < minZ){
	    minZ = temp[i].z;
	  }
	  if(temp[i].z > maxZ){
	    maxZ = temp[i].z;
	  }
	}

  
  glm::vec3 cornerA = glm::vec3(minX, minY, minZ);
  glm::vec3 cornerB = glm::vec3(maxX, maxY, maxZ);
  
  return BoundingBox(cornerA, cornerB);
}

bvhNode::bvhNode(std::vector<Geometry*> A, int axis){
  int N = A.size();
  
  if(N == 1){
    this->left = A[0];
    this->right = NULL;
    this->boundingBox = A[0]->getBoundingBox();
  }
  
  else if(N == 2){
    this->left = A[0];
    this->right = A[1];
    this->boundingBox = combineBoundingBox(A[0]->getBoundingBox(), A[1]->getBoundingBox());
  }
  
  else{
    std::vector<Geometry*> temp;
    
     for(int i = 0; i < A.size(); i++){
       for(int j = 0; j < temp.size(); j++){
	 if(i == 0){
	  temp.push_back(A[i]); 
	  break;
	 }
	 if(A[i]->getCenter()[axis] < temp[j]->getCenter()[axis]){
	   temp.insert(temp.begin() + j, A[i]);
	   break;
	 }
       }       
       if( j == temp.size()){
	 temp.push_back(A[i]);
       }
      }
     
      std::vector<Geometry*> half1;
      std::vector<Geometry*> half2;     
            
      for(int i = 0; i < temp.size(); i++){
	if(i <= ((temp.size() / 2) - 1)){
	  half1.push_back(temp[i]);
	}
	else{

	  half2.push_back(temp[i]);
	}
      }
      
      left = new bvhNode(half1, (axis + 1) % 3);
      right = new bvhNode(half2, (axis + 1) % 3);
      this->boundingBox = combineBoundingBox(left->getBoundingBox(), right->getBoundingBox());
  }
}

  Geometry* bvhNode::intersect(Ray* ray, float t0, float t1){
    float temp = boundingBox.intersect(ray);
    
    Geometry* theHit = NULL;
    Geometry* tempHit1 = NULL;
    Geometry* tempHit2 = NULL;
    if(temp != -1.0f){
      if(left != NULL){
	tempHit1 = left->intersect(ray, 0.0f, ray->getTime());
      }
      if(right != NULL){
	tempHit2 = right->intersect(ray, 0.0f, ray->getTime());
      }
      if(tempHit2 != 0){
	return tempHit2;
      }
      else{
	return tempHit1;
      }
    }
    
    else{
      return NULL;
    }
  }