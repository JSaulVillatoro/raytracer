#include "core/shaders.h"
#include "geometry/geometry.h"

glm::vec4 shade(Ray* ray, std::vector<Light_Source*> lightSources, std::vector<Geometry*> collidedObjects, Geometry* closestObject, int reflectCounter, int shader){

 glm::vec4 ambientLight; 
 glm::vec4 lightColor;
 glm::vec4 ambient;
 glm::vec4 specular;
 glm::vec4 diffuse;
 glm::vec4 reflective;
 
    for(unsigned int i = 0; i < lightSources.size(); i++){
      ambientLight += lightSources[i]->getColor().getColorVector();
      }
 
  ambient = closestObject->getPigment().getColor().getColorVector() * closestObject->getFinish().getAmbient();
 
 ambient.x = ambient.x * ambientLight.x;
 ambient.y = ambient.y * ambientLight.y;
 ambient.z = ambient.z * ambientLight.z;
 
 glm::vec3 normal = ray->getNormal();
 
 normal = glm::normalize(normal);
 
     for(unsigned int i = 0; i < lightSources.size(); i++){

 
  lightColor = lightSources[i]->getColor().getColorVector();
 
 glm::vec3 lightVector = lightSources[i]->getPosition() - ray->getIntersectionPoint();
 lightVector = glm::normalize(lightVector);
 
 if(reflectCounter == -1){
   return glm::vec4(1.0f);
 }
 
 
 if(closestObject->getFinish().getRefraction() > 0.0 && reflectCounter != 0){
   
      float tempIOR;
   
   if( ray->getIOR() == closestObject->getFinish().getIor()){
    tempIOR = ray->getIOR();
   }
   else{
    tempIOR =  closestObject->getFinish().getIor();
   }

   Ray* reflectedRay = new Ray();
   reflectedRay->setPoint(ray->getIntersectionPoint());
   
   glm::vec3 currentRayNormalizedD = glm::normalize(ray->getDirection());
  
   float reflectedNdotL = std::max(0.0f, glm::dot(normal, (-1.0f * currentRayNormalizedD)));   
   glm::vec3 reflectedD = currentRayNormalizedD + 2.0f * reflectedNdotL * normal;
   
   
   reflectedRay->setDirection(reflectedD);
   reflectedRay->setPoint(reflectedRay->getPoint() + 0.0001f * reflectedRay->getDirection());
   
   Ray* theT = new Ray();
   
   theT->setPoint(ray->getIntersectionPoint());
   float c;
   Geometry* geoHit = NULL;
   float temp = -1.0f;
   float lowestTime = std::numeric_limits<double>::infinity();
   
   glm::vec4 reflectedColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
   
   for(unsigned int k = 0; k < collidedObjects.size(); k++){
	temp = collidedObjects[k]->intersect(reflectedRay, 0.0f, reflectedRay->getTime());
	if(temp != -1.0f){
	  geoHit = collidedObjects[k];
	  lowestTime = temp;
	  reflectedRay->setTime(lowestTime);
	}
      }
      
      if(geoHit != NULL){
	reflectedRay->setTime(lowestTime);
	reflectedColor = shade(reflectedRay, lightSources, collidedObjects, geoHit, (reflectCounter - 1), shader);
      }
   
      if(glm::dot(currentRayNormalizedD, normal) <= 0.0f){
     //std::cout << "refraction: " << reflectCounter << std::endl;
     //std::cout << "normalizeD x: " << currentRayNormalizedD.x << " y: " << currentRayNormalizedD.y << " z: " << currentRayNormalizedD.z << std::endl;
     //std::cout << "normal x: " << normal.x << " y: " << normal.y << " z: " << normal.z << std::endl;

     //std::cout << "NUMBAH: " << glm::dot(currentRayNormalizedD, normal) << std::endl;
     //return glm::vec4(fabs(normal.x), fabs(normal.y), fabs(normal.z), 1.0f);
     refract(currentRayNormalizedD, normal, ray->getIOR(), tempIOR, *theT);       
     c = -1.0f * glm::dot(currentRayNormalizedD, normal);
   }
   
   else{
          //return glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

     bool result = refract(currentRayNormalizedD, (-1.0f * normal),ray->getIOR(), 1.0f, *theT ); 
          if(result == true){
       c = glm::dot(theT->getDirection(), normal);
     }
     
     else{
       return reflectedColor;
     }
   }
   
  float R0 = ((ray->getIOR() - tempIOR) * (ray->getIOR() - tempIOR)) / 
	      ((ray->getIOR() + tempIOR) * (ray->getIOR() + tempIOR));
  float R = R0 + (1.0f - R0) * pow((1.0f - c), 5.0f);
      
  //std::cout << "ray: " << ray->getIOR() << std::endl;
   // std::cout << "hit: " << tempIOR << std::endl;

 
  geoHit = NULL;
  temp = -1.0f;
  lowestTime = std::numeric_limits<double>::infinity();
   
   glm::vec4 refractedColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
   
   for(unsigned int k = 0; k < collidedObjects.size(); k++){
	temp = collidedObjects[k]->intersect(theT, 0.0f, theT->getTime());
	if(temp != -1.0f){
	  geoHit = collidedObjects[k];
	  lowestTime = temp;
	  theT->setTime(lowestTime);
	}
      }
      if(geoHit != NULL){
	theT->setTime(lowestTime);
	refractedColor = shade(theT, lightSources, collidedObjects, geoHit, reflectCounter - 1, shader);
      }
  
  //std::cout << R0 << std::endl;
  
  //std::cout << "x: " << reflectedColor.x << " y: " << reflectedColor.y << " z: " << reflectedColor.z << std::endl;

  return ((R * reflectedColor) + ((1.0f - R) * refractedColor));
  
 }  
 
 
 
 Ray* shadowFeeler = new Ray();
 
 shadowFeeler->initializeRay(ray->getIntersectionPoint(), lightSources[i]->getPosition());
 
 bool inShadow = false;
 
 Geometry* geoHit = NULL;
 float temp = -1.0f;
 float lowestTime = std::numeric_limits<double>::infinity();
 
 for(unsigned int k = 0; k < collidedObjects.size(); k++){
  temp = collidedObjects[k]->intersect(shadowFeeler, 0.0f, shadowFeeler->getTime());
  if( temp != -1.0f){
	  geoHit = collidedObjects[k];
	  lowestTime = temp;
	  shadowFeeler->setTime(lowestTime);
   }
  }
  
   if(geoHit != NULL){
     if(geoHit != closestObject){
       inShadow = true;
     }  
    }
 
 if(inShadow == true){
   
   diffuse = glm::vec4(0.0f);
   specular = glm::vec4(0.0f);
  break;
 }
 
 else{
 
 float NdotL = std::max(0.0f, glm::dot(normal, lightVector));
 
 glm::vec4 thisDiffuse;
 
 thisDiffuse = closestObject->getFinish().getDiffuse() * NdotL * closestObject->getPigment().getColor().getColorVector();
 thisDiffuse.x = thisDiffuse.x * lightColor.x;
 thisDiffuse.y = thisDiffuse.y * lightColor.y;
 thisDiffuse.z = thisDiffuse.z * lightColor.z;
 
 diffuse += thisDiffuse;
  
 if(shader == 0){
 
 glm::vec3 R = -1.0f * lightVector + 2.0f * NdotL * normal;
 
 R = glm::normalize(R); 

 glm::vec3 V = -1.0f * ray->getDirection(); 
 
 V = glm::normalize(V);
 
 float VdotR = std::max(0.0f, glm::dot(V,R));
 
 glm::vec4 thisSpecular;
 
 thisSpecular = closestObject->getFinish().getSpecular() * pow(VdotR, 1.0f / closestObject->getFinish().getRoughness()) * closestObject->getPigment().getColor().getColorVector();
 thisSpecular.x = thisSpecular.x * lightColor.x;
 thisSpecular.y = thisSpecular.y * lightColor.y;
 thisSpecular.z = thisSpecular.z * lightColor.z;
 
 specular += thisSpecular;
 }
 else if(shader ==  1){
   glm::vec3 V = -1.0f * ray->getDirection(); 
   V = glm::normalize(V);
   
  glm::vec3 H = lightVector + V;
  H = glm::normalize(H);
  
  float angle = glm::dot(normal, H);
  float toRaise = angle / closestObject->getFinish().getRoughness();
  toRaise = pow(toRaise, 2.0f);
  toRaise *= -1.0f;
  
  float spec = pow(M_E, toRaise);
  
  glm::vec4 thisSpecular;
  
 thisSpecular = closestObject->getFinish().getSpecular() * spec * closestObject->getPigment().getColor().getColorVector();
 thisSpecular.x = thisSpecular.x * lightColor.x;
 thisSpecular.y = thisSpecular.y * lightColor.y;
 thisSpecular.z = thisSpecular.z * lightColor.z;
 
 specular += thisSpecular;
 }
}
     } 
 glm::vec4 theColor = ambient + diffuse + specular;
 
 if(closestObject->getFinish().getReflection() > 0.0 && reflectCounter != 0){
      
   Ray* reflectedRay = new Ray();
   reflectedRay->setPoint(ray->getIntersectionPoint());
   
   glm::vec3 currentRayNormalizedD = glm::normalize(ray->getDirection());
  
   float reflectedNdotL =  glm::dot(normal, (-1.0f * currentRayNormalizedD));   
   glm::vec3 reflectedD = currentRayNormalizedD + 2.0f * reflectedNdotL * normal;
   
   reflectedRay->setDirection(reflectedD);
   reflectedRay->setPoint(reflectedRay->getPoint() + 0.0001f * reflectedRay->getDirection());
   
   Geometry* geoHit = NULL;
   float temp = -1.0f;
   float lowestTime = std::numeric_limits<double>::infinity();
   
   for(unsigned int k = 0; k < collidedObjects.size(); k++){
	temp = collidedObjects[k]->intersect(reflectedRay, 0.0f, reflectedRay->getTime());
	if(temp != -1.0f){
	  geoHit = collidedObjects[k];
	  lowestTime = temp;
	  reflectedRay->setTime(lowestTime);
	}
      }
      
      if(geoHit != NULL){
	reflectedRay->setTime(lowestTime);
	theColor = (1.0f - closestObject->getFinish().getReflection()) * theColor + closestObject->getFinish().getReflection() * shade(reflectedRay, lightSources, collidedObjects, geoHit, reflectCounter - 1, shader);
      }
    }   

 theColor.w = closestObject->getPigment().getColor().getColorVector().w;
 
 return theColor;
}

bool refract(glm::vec3 d, glm::vec3 n, float prevIOR, float newIOR, Ray &t){
  float ior = prevIOR / newIOR;
  float DdotN = glm::dot(d,n);
  
  float underRoot = 1.0f - ((ior * ior) * (1.0f - (DdotN * DdotN)));
  
  if(underRoot < 0.0f){
    return false;
  }
  
  float num = sqrt(underRoot);
  
  glm::vec3 rightTerm = n * num;
  glm::vec3 leftTerm = ior * (d - (n * DdotN));
  
  glm::vec3 term = leftTerm - rightTerm;
  
  t.setDirection(term);
  t.setPoint(t.getPoint() + 0.0001f * t.getDirection());
  t.setIOR(newIOR);
  
 return true; 
}