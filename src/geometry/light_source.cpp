#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "light_source.h"
#include "../core/parser.h"

void Light_Source::parse(std::ifstream& in){
  std::string tempString;
  in >> tempString;
  
  if(tempString != "{"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: {" << std::endl;
    exit(0);
  }
  
  setVector(in, position);
  in >> tempString;
  
  if(tempString == "color"){	    
    color.parseColor(in);
  }
  else{
    std::cout << "Incorrect format" << std::endl;
    exit(0);
  }
  
  in >> tempString;
  
  if(tempString != "}"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: }" << std::endl;
    exit(0);
  }
}

void Light_Source::print(){
  std::cout << "=== Light Source ===" << std::endl;
  std::cout << "position: <" << position.x << ", " << position.y << ", " << position.z << ">" << std::endl; 
  color.printColor();
  std::cout << std::endl;  
}

void Light_Source::intersect(Ray* ray){}