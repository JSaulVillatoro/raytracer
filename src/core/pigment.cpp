#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "pigment.h"

void Pigment::parsePigment(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  fin >> tempString;
  
  if(tempString == "color"){
    color.parseColor(fin);
  }  
  else{
    std::cout << "Unidentified keyword: " << tempString << std::endl;
    exit(0);
  }
  
  fin >> tempString;
  
  if(tempString != "}"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: }" << std::endl;
    exit(0);
  }
}

void Pigment::printPigment(){
  std::cout << "~~~ Pigment ~~~" << std::endl;
  color.printColor();
}