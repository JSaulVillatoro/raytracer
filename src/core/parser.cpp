#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include "../third_party/glm/glm.hpp"
#include "parser.h"
#include "color.h"

bool isComment(std::ifstream& fin){
  char c = fin.get();
  std::string temp;
  int count = 0;
  
  while(count < 2){
    if(!isspace(c)){
      temp += c;
      count++;
    }
    c = fin.get();
  }
  
  if(temp == "//"){
    return true;
  }
   else{
    fin.seekg(-3, fin.cur);
    return false;
   }
  }

int setVector(std::ifstream& fin, glm::vec3& vector){
  std::string tempString;
  int count = 0;
  char c;
  
  c = fin.get();
  
  while(c != '<'){
    c = fin.get();
  }
  
  c = fin.get();

  std::string temp;
  
  while(c != '>'){  
    if(!isspace(c)){
      if(isdigit(c) || c == '-' || c == '+' || c == '.'){
	temp += c;
      }
      else if( c == ',' ){
	std::istringstream(temp) >> vector[count];
	temp.clear();
	count++;
      }
      else{
	std::cout <<"wec" << c << std::endl;
	std::cout << "Format wrong in vector" << std::endl;
	exit(1);
      }
    }
    c = fin.get();
  }
  
  std::istringstream(temp) >> vector[count];
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
  
    c = fin.get();

  
  std::string temp;
  
  while(c != '>'){  
    if(!isspace(c)){
      if(isdigit(c) || c == '-' || c == '+' || c == '.'){
	temp += c;
      }
      else if( c == ',' ){
	std::istringstream(temp) >> vector[count];
	temp.clear();
	count++;
      }
      else{
	std::cout << "Format wrong in vector" << std::endl;
	exit(1);
      }
    }
    c = fin.get();
  }
  
  std::istringstream(temp) >> vector[count];
  return 0;
}