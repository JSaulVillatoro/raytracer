#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "plane.h"
#include "../core/parser.h"

void Plane::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, normal);
  fin >> distance;
  
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

void Plane::print(){
  std::cout << "=== Plane ===" << std::endl; 
  std::cout << "normal: <" << normal.x << ",  " << normal.y << ", " << normal.z << ">" << std::endl; 
  std::cout << "distance: " << distance << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;  
}