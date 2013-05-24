#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "core/Image.h"
#include "core/types.h"
#include "core/camera.h"
#include "core/ray.h"
#include "core/color.h"
#include "core/shaders.h"
#include "core/bvhNode.h"
#include "geometry/light_source.h"
#include "geometry/sphere.h"
#include "geometry/cone.h"
#include "geometry/plane.h"
#include "geometry/box.h"
#include "geometry/triangle.h"

Camera* camera;

std::vector<Geometry*> world_geometry;
std::vector<Geometry*> other_geometry;

std::vector<Geometry*> planes;
std::vector<Light_Source*> light_sources;
bvhNode* root;

float offsetMe(){
  float toReturn = ((float)rand() / (RAND_MAX)) / 1000.0f;
  float deter = ((float) rand() / (RAND_MAX)) + 1.0f;
  if (deter <= 0.5f){
    toReturn = -1.0f * toReturn;
  }
  return toReturn;
}

void parseFile(std::string fileName){
  std::ifstream fin(fileName.c_str());
  std::string tempString;
  
  fin >> tempString;
  
  while(!fin.eof()){
    if(tempString[0] == '/' && tempString[1] == '/'){
      getline(fin, tempString);
    }
    else{
	/* only add implemented geometry to list.
	REMEMBER TO CHANGE THIS. */

      if(tempString == "sphere"){
	world_geometry.push_back(new Sphere(fin));
      }
      else if(tempString == "cone"){
	other_geometry.push_back(new Cone(fin));
	//world_geometry.push_back(new Cone(fin));
      }
      else if(tempString == "plane"){
	planes.push_back(new Plane(fin));
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
  root = new bvhNode(world_geometry, 0);
 // std::cout << " x: " << root->getBoundingBox().getCorner1().x << " y: " << root->getBoundingBox().getCorner1().y << " z: " << root->getBoundingBox().getCorner1().z << std::endl;
 // std::cout << " x: " << root->getBoundingBox().getCorner2().x << " y: " << root->getBoundingBox().getCorner2().y << " z: " << root->getBoundingBox().getCorner2().z << std::endl;

  
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
  clock_t start, end;
  double runTime;
  start = clock();
  if(argc != 7){
    std::cout << "Incorrect number of arguments." << std::endl;
    std::cout << "Usage: " << argv[0] << " [image_width] [image_height] -S [p,g] -I [input_file]" << std::endl;
    exit(0);
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  
  int shader;
 
  if(strcmp(argv[3], "-S") == 1){
    std::cout << "Usrfrfage: " << argv[0] << " [image_width] [image_height] -S [p,g] -I [input_file]" << std::endl;
    exit(0);
  }
  
    if(strcmp(argv[4], "p") == 0){
      shader = 0;
    }
  
    else if(strcmp(argv[4], "g") == 0){
      shader = 1;
    }  
    
    else{
      std::cout << "Shading model not recognized." << std::endl;
      std::cout << "Usage: " << argv[0] << " [image_width] [image_height] -S [p,g] -I [input_file]" << std::endl;
      exit(0);
    }
    
    color_t clr;

  clr.r = 0.5;
  clr.g = 0.5;
  clr.b = 0.9;
  
  camera = new Camera();
  
  if(strcmp(argv[5], "-I") == 1){
    std::cout << "Usage: " << argv[0] << " [image_width] [image_height] -S [p,g] -I [input_file]" << std::endl;
    exit(0);
  }
  
  parseFile(argv[6]);
  
  Image img(width, height);
  Ray* rays[width][height];
  Ray* pixelRays[9];
  

  for (int i=0; i < width; i++) {
    for (int j=0; j < height; j++) {
      rays[i][j] = new Ray();
      rays[i][j]->initializeRay(*camera, width, height, i, j);
    }
  }
  
  Geometry* geometryHit;
  float lowestTime;
  
  rays[0][1]->getPoint() - rays[0][0]->getPoint();
  
  float offset = 0.5f;
  //float offset = 0.5f;
  
  srand(5);
  
  for (int i=0; i < width; i++){
    for (int j=0; j < height; j++){
      
      
      for(int k = 0; k < 9; k++){
	pixelRays[k] = new Ray();
	    }
      
      
            pixelRays[0]->initializeRay(*camera, width, height, i - offset + offsetMe(), j - offset + offsetMe());
            pixelRays[1]->initializeRay(*camera, width, height, i + offsetMe(), j - offset + offsetMe());
            pixelRays[2]->initializeRay(*camera, width, height, i + offset + offsetMe(), j - offset + offsetMe());
            pixelRays[3]->initializeRay(*camera, width, height, i - offset + offsetMe(), j + offsetMe());
            pixelRays[4]->initializeRay(*camera, width, height, i + offsetMe(), j + offsetMe());
            pixelRays[5]->initializeRay(*camera, width, height, i + offset + offsetMe(), j + offsetMe());
            pixelRays[6]->initializeRay(*camera, width, height, i - offset + offsetMe(), j + offset + offsetMe());
            pixelRays[7]->initializeRay(*camera, width, height, i + offsetMe(), j + offset + offsetMe());
            pixelRays[8]->initializeRay(*camera, width, height, i + offset + offsetMe(), j + offset + offsetMe());

            
	    glm::vec4 averageColor = glm::vec4(0.0f);
	    for(int k = 0; k < 9; k++){
	    averageColor += shade(pixelRays[k], light_sources, world_geometry, 6, shader, root, planes);
	    }
	    
	    averageColor = averageColor / 9.0f;

	rays[i][j]->setColor(averageColor);
	//rays[i][j]->setColor(shade(rays[i][j], light_sources, world_geometry, 6, shader, root, planes));
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
    
    //printInfo();
    char temp[strlen(argv[6])];
    strcpy(temp, argv[6]);
    
    
    argv[6][strlen(argv[6]) - 1] = 'a';
    argv[6][strlen(argv[6]) - 2] = 'g';
    argv[6][strlen(argv[6]) - 3] = 't';
    
  // write the targa file to disk
  img.WriteTga((char *)argv[6], false); 
  // true to scale to max color, false to clamp to 1.0
  end = clock();
  runTime = (end - start) / (double) CLOCKS_PER_SEC ;
  printf ("Run time for file: %s is %g seconds.\n", temp, runTime);
  return 0;
}