#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "box.h"
#include "../core/parser.h"

void Box::parse(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(fin, corner1);
  setVector(fin, corner2);
  
  fin >> tempString;

  while(tempString != "}"){
    if(tempString == "pigment"){
      setPigment(fin);
    }
    else if(tempString == "finish"){
      setFinish(fin);
    }
    else{
      std::cout << "Unidentified keyword : " << tempString << std::endl;
      exit(0);
    }
    fin >> tempString;
  }
}

void Box::print(){
  std::cout << "=== Box ===" << std::endl; 
  std::cout << "Corner 1: <" << corner1.x << ",  " << corner1.y << ", " << corner1.z << ">" << std::endl; 
  std::cout << "Corner 2: <" << corner2.x << ",  " << corner2.y << ", " << corner2.z << ">" << std::endl; 
  getPigment().printPigment();
  getFinish().printFinish();
  std::cout << std::endl;
}