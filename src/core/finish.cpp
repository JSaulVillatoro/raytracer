#include <iostream> 
#include <cstdlib>
#include <fstream>
#include <string>
#include "finish.h"

void Finish::parseFinish(std::ifstream& fin){
  char c = fin.get();
  std::string tempString;
  
  while(c != '{'){
    c = fin.get();
  }
  
  fin >> tempString;
  
  while(tempString != "}"){
    
    float value;
    fin >> value;
        
    if( tempString == "ambient"){
      ambient = value;
    }
    else if( tempString == "diffuse"){
      diffuse = value;
    }
    else if( tempString == "specular"){
      specular = value;
    }
    else if( tempString == "roughness"){
      roughness = value;
    }
    else if( tempString == "reflection"){
      reflection = value;
    }
    else if( tempString == "refraction"){
      refraction = value;
    }
    else if( tempString == "ior"){
      ior = value;
    }
    else if( tempString == "gloss"){
      glossy = value;
    }
    else{
      std::cout << "Unidentified keyword: " << tempString << std::endl;
      exit(0);
    }
    
    fin >> tempString;
  }
}

void Finish::printFinish(){
  std::cout << "~~~ Finish ~~~" << std::endl;
  std::cout << "ambient: " << ambient <<std::endl;
  std::cout << "diffuse: " << diffuse <<std::endl;
  std::cout << "specular: " << specular <<std::endl;
  std::cout << "roughness: " << roughness <<std::endl;
  std::cout << "reflection: " << reflection <<std::endl;
  std::cout << "refraction: " << refraction <<std::endl;
  std::cout << "ior: " << ior << std::endl;
}