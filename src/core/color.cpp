#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "color.h"
#include "parser.h"

void Color::parseColor(std::ifstream& fin){
  std::string tempString;
  fin >> tempString;
  
  if(tempString != "rgb" && tempString != "rgbf"){
    std::cout << "Unidentified keyword: " << tempString << std::endl;
    exit(0);
  }
  setVector4(fin, color);
}

void Color::printColor(){
  std::cout << "~~~ Color ~~~" << std::endl;
  std::cout << "<" << color[0] << ", " << color.y << ", " << color.z << ", " << color.w << ">" << std::endl;
}