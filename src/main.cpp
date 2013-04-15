#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "core/Image.h"
#include "core/types.h"
#include "core/camera.h"
#include "core/ray.h"
#include "core/color.h"
#include "geometry/light_source.h"
#include "geometry/sphere.h"
#include "geometry/cone.h"
#include "geometry/plane.h"
#include "geometry/box.h"
#include "geometry/triangle.h"

Camera* camera;

std::vector<Geometry*> world_geometry;
std::vector<Light_Source*> light_sources;

void parseFile(std::string fileName){
  std::ifstream fin(fileName.c_str());
  std::string tempString;
  
  fin >> tempString;
  
  while(!fin.eof()){   
    if(tempString == "//"){
      getline(fin, tempString);
    }
    else{
      if(tempString == "sphere"){
	world_geometry.push_back(new Sphere(fin));
      }
      else if(tempString == "cone"){
	world_geometry.push_back(new Cone(fin));
      }
      else if(tempString == "plane"){
	world_geometry.push_back(new Plane(fin));
      }
      else if(tempString == "box"){
	world_geometry.push_back(new Box(fin));
      }
      else if(tempString == "triangle"){
	world_geometry.push_back(new Triangle(fin));
      }
      else if(tempString == "light_source"){
	light_sources.push_back(new Light_Source(fin));
      }
      else if(tempString == "camera"){
	camera->parseCamera(fin);
      }
      else{
	std::cout << "Unidentified keyword: " << tempString << std::endl;
	exit(0);
      }
    }
    fin >> tempString;
  }
}

void printInfo(){
  camera->printCamera();
  
  for(unsigned int i = 0; i < light_sources.size(); i++){
    light_sources[i]->print(); 
  }
  
  for(unsigned int i = 0; i < world_geometry.size(); i++){
    world_geometry[i]->print(); 
  }
}

int main(int argc,char *argv[]){ 
  if(argc != 5){
    std::cout << "Incorrect number of arguments." << std::endl;
    std::cout << "Usage: " << argv[0] << " [image_width] [image_height] -I [input_file]" << std::endl;
    exit(0);
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  
  
    color_t clr;

  clr.r = 0.5;
  clr.g = 0.5;
  clr.b = 0.9;
  
  camera = new Camera();
  parseFile(argv[4]);
  
  Image img(width, height);
  
  Ray* rays[width][height];
  

  for (int i=0; i < width; i++) {
    for (int j=0; j < height; j++) {
      rays[i][j] = new Ray();
      rays[i][j]->initializeRay(*camera, width, height, i, j);
    }
  }
  
  for(unsigned int k = 0; k < world_geometry.size(); k++){
    for (int i=0; i < width; i++) {
      for (int j=0; j < height; j++) {
	world_geometry[k]->intersect(rays[i][j]);
      }
    }
  }
  
  for (int i=0; i < width; i++) {
    for (int j=0; j < height; j++) {
      glm::vec4 tempColor = rays[i][j]->getColor().getColorVector();
      clr.r = tempColor.x;
      clr.g = tempColor.y;
      clr.b = tempColor.z;
      img.pixel(i, j, clr);
      }
    }
    
    argv[4][strlen(argv[4]) - 1] = 'a';
    argv[4][strlen(argv[4]) - 2] = 'g';
    argv[4][strlen(argv[4]) - 3] = 't';
    
  // write the targa file to disk
  img.WriteTga((char *)argv[4], true); 
  // true to scale to max color, false to clamp to 1.0
  return 0;
}