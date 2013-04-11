#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "core/camera.h"
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
    std::cout << "Usage: " << argv[0] << " [width] [height] -I [input_file]" << std::endl;
    exit(0);
  }
  camera = new Camera();
  parseFile(argv[4]);
  printInfo();
  return 0;
}