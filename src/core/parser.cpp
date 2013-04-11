#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "../third_party/glm/glm.hpp"
#include "parser.h"
#include "color.h"

int setVector(std::ifstream& fin, glm::vec3& vector){
  std::string tempString;
  int count = 0;
  char c;
  
  c = fin.get();
  
  while(c != '<'){
    c = fin.get();
  }
  
  while(tempString != ">" && tempString != ">,"){  
    fin >> vector[count];
    count++; 
    
    fin >> tempString;
  }
  return 0;
}

int setVector4(std::ifstream& fin, glm::vec4& vector){
  std::string tempString;
  int count = 0;
  char c;
  
  c = fin.get();
  
  while(c != '<'){
    c = fin.get();
  }
  
  while(tempString != ">" && tempString != ">,"){
    fin >> vector[count];
    count++; 
    
    fin >> tempString;
  }
  return 0;
}