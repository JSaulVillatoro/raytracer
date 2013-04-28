#include "core/shaders.h"
#include "geometry/geometry.h"

glm::vec4 shade(Ray* ray, std::vector<Light_Source*> lightSources, std::vector<Geometry*> collidedObjects, Geometry* closestObject, int reflectCounter, int shader){

 glm::vec4 lightColor;
 glm::vec4 ambient;
 glm::vec4 specular;
 glm::vec4 diffuse;
 glm::vec4 reflective;
 
 lightColor = lightSources[0]->getColor().getColorVector();
 ambient = closestObject->getPigment().getColor().getColorVector() * closestObject->getFinish().getAmbient();
 
 ambient.x = ambient.x * lightColor.x;
 ambient.y = ambient.y * lightColor.y;
 ambient.z = ambient.z * lightColor.z;

 
 glm::vec3 normal = ray->getNormal();
 
 normal = glm::normalize(normal);
 
 //std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
 
 glm::vec3 lightVector = lightSources[0]->getPosition() - ray->getIntersectionPoint();
 lightVector = glm::normalize(lightVector);
 
 Ray* shadowFeeler = new Ray();
 
 shadowFeeler->initializeRay(ray->getIntersectionPoint(), lightSources[0]->getPosition());
 
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
    // if(geoHit != closestObject){
       inShadow = true;
    // }  
    }
 
 if(inShadow == true){
   
   diffuse = glm::vec4(0.0f);
   specular = glm::vec4(0.0f);
 
 }
 
 else{
 
 float NdotL = std::max(0.0f, glm::dot(normal, lightVector));
 
 diffuse = closestObject->getFinish().getDiffuse() * NdotL * closestObject->getPigment().getColor().getColorVector();
 diffuse.x = diffuse.x * lightColor.x;
 diffuse.y = diffuse.y * lightColor.y;
 diffuse.z = diffuse.z * lightColor.z;
  
 if(shader == 0){
 
 glm::vec3 R = -1.0f * lightVector + 2.0f * NdotL * normal;
 
 R = glm::normalize(R); 

 glm::vec3 V = -1.0f * ray->getDirection(); 
 
 V = glm::normalize(V);
 
 float VdotR = std::max(0.0f, glm::dot(V,R));
 
 specular = closestObject->getFinish().getSpecular() * pow(VdotR, 1.0f / closestObject->getFinish().getRoughness()) * closestObject->getPigment().getColor().getColorVector();
 specular.x = specular.x * lightColor.x;
 specular.y = specular.y * lightColor.y;
 specular.z = specular.z * lightColor.z;
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
  
  
 specular = closestObject->getFinish().getSpecular() * spec * closestObject->getPigment().getColor().getColorVector();
 specular.x = specular.x * lightColor.x;
 specular.y = specular.y * lightColor.y;
 specular.z = specular.z * lightColor.z;
 }
}
 
 glm::vec4 theColor = ambient + diffuse + specular;
 
 if(closestObject->getFinish().getReflection() > 0.0 && reflectCounter != 0){
      
   Ray* reflectedRay = new Ray();
   reflectedRay->setPoint(ray->getIntersectionPoint());
   
   glm::vec3 currentRayNormalizedD = glm::normalize(ray->getDirection());
  
   float reflectedNdotL = std::max(0.0f, glm::dot(normal, (-1.0f * currentRayNormalizedD)));   
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
	theColor = theColor + (1.0f - closestObject->getFinish().getReflection()) * theColor + closestObject->getFinish().getReflection() * shade(reflectedRay, lightSources, collidedObjects, geoHit, reflectCounter - 1, shader);
      }
    }   
 theColor.w = closestObject->getPigment().getColor().getColorVector().w;
 
 return theColor;
}