#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <fstream>
#include <vector>
#include "../third_party/glm/glm.hpp"
#include "../geometry/geometry.h"

class bvhNode: public Geometry{
 public:  
  bvhNode(std::vector<Geometry*> A, int axis);
  virtual Geometry* intersect(Ray* ray, float t0, float t1);
  virtual void parse(std::ifstream& fin){}
  virtual void print(){}
  virtual glm::vec3 calculateNormal(Ray* ray){return glm::vec3(0.0f);}
  virtual void setBoundingBox(){}
 private:   
   Geometry* left;
   Geometry* right;
};
#endif
