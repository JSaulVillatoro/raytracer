#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "camera.h"
#include "parser.h"

void Camera::parseCamera(std::ifstream& fin){
  char c = fin.get();
  std::string tempString;
    
  while(c != '{'){
    c = fin.get();
  }
  fin >> tempString;
  
  while(tempString != "}"){
    if(tempString[0] == '/' && tempString[1] == '/'){
      getline(fin, tempString);
    }
    
    else{
    if(tempString == "location"){
      setVector(fin, location);
    }
    else if(tempString == "up"){
      setVector(fin, up);
    }
    else if(tempString == "right"){
      setVector(fin, right);
    }
    else if(tempString == "look_at"){
      setVector(fin, look_at);
    }
    else if(tempString == "direction"){
      setVector(fin, direction);
    }
    else{
      std::cout << "Unidentified keyword: " << tempString << std::endl;
      exit(0);
    }
    }
    fin >> tempString;   
  } 
  
  if(tempString != "}"){
    std::cout << "Incorrect format, found: " << tempString << ", expected: }" << std::endl;
    exit(0);
  }
}

void Camera::printCamera(){
  std::cout << "=== Camera ===" << std::endl;
  std::cout << "location: <" << location.x << ", " << location.y << ", " << location.z << ">" << std::endl;
  std::cout << "up: <" << up.x << ", " << up.y << ", " << up.z << ">" << std::endl;
  std::cout << "right: <" << right.x << ", " << right.y << ", " << right.z << ">" << std::endl;
  std::cout << "look_at: <" << look_at.x << ", " << look_at.y << ", " << look_at.z << ">" << std::endl;
  std::cout << std::endl;
}