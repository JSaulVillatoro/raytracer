#ifndef FINISH_H
#define FINISH_H
#include <fstream>

class Finish{
 public:
  Finish(){
    ambient = 0.0f;
    diffuse = 0.0f;
    specular = 0.0f;
    roughness = 0.0f;
    reflection = 0.0f;
    refraction = 0.0f;
    ior = 0.0f;
  }
  
  virtual ~Finish(){};
  void parseFinish(std::ifstream& fin);
  float getAmbient(){ return ambient;}
  float getDiffuse(){ return diffuse;}
  float getSpecular(){ return specular;}
  float getRoughness(){ return roughness;}
  float getReflection(){ return reflection;}
  float getRefraction(){ return refraction;}
  float getIor(){ return ior;}

  void printFinish();
  
 private:
  float ambient;
  float diffuse;
  float specular;
  float roughness;
  float reflection;
  float refraction;
  float ior;
};
#endif
