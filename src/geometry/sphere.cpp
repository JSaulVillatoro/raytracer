#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "sphere.h"
#include "../core/parser.h"

void Sphere::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, position);
  
  fin >> radius;
  //pesky comma
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

void Sphere::print(){
  std::cout << "=== Sphere ===" << std::endl; 
  std::cout << "position: <" << position.x << ",  " << position.y << ", " << position.z << ">" << std::endl; 
  std::cout << "radius: " << radius << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}