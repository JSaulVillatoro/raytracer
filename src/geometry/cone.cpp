#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cone.h"
#include "../core/parser.h"

void Cone::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  setVector(fin, base_point);
  
  fin >> base_radius;
  //commas, man
  fin >> tempString;

  setVector(fin, cap_point);
  fin >> cap_radius;
  
  fin >> tempString;

  while(tempString != "}"){
    if(tempString == "pigment"){
      setPigment(fin);
    }
    
    else if(tempString == "finish"){
      setFinish(fin);
    }
    else{
      std::cout << "Unidentified keyword: " << tempString << std::endl;
      exit(0);
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

void Cone::intersect(Ray* ray){}