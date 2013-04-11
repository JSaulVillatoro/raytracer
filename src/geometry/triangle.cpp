#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "triangle.h"
#include "../core/parser.h"

void Triangle::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, corner1);
  setVector(fin, corner2);
  setVector(fin, corner3);    
  
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

void Triangle::print(){
  std::cout << "=== Triangle ===" << std::endl; 
  std::cout << "Corner 1: <" << corner1.x << ",  " << corner1.y << ", " << corner1.z << ">" << std::endl;
  std::cout << "Corner 2: <" << corner2.x << ",  " << corner2.y << ", " << corner2.z << ">" << std::endl;
  std::cout << "Corner 3: <" << corner3.x << ",  " << corner3.y << ", " << corner3.z << ">" << std::endl;
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}