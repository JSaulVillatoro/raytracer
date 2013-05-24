#include "core/shaders.h"
#include "geometry/geometry.h"

glm::vec4 shade(Ray* ray, std::vector<Light_Source*> lightSources, std::vector<Geometry*> collidedObjects, int reflectCounter, int shader, bvhNode* node, std::vector<Geometry*> planes){
  Geometry* closestObject = findClosestObject(ray, collidedObjects, node, planes);
  
  if(closestObject == NULL){
    return ray->getColor().getColorVector();
  }
  else{
    glm::vec4 lightColor;
    glm::vec4 ambient;
    glm::vec4 specular;
    glm::vec4 diffuse;
    glm::vec4 reflective;
    
    glm::vec3 normal = ray->getNormal();
    normal = glm::normalize(normal);
    
    for(unsigned int i = 0; i < lightSources.size(); i++){
      lightColor = lightSources[i]->getColor().getColorVector();
      
      glm::vec4 thisAmbient;
      thisAmbient = closestObject->getPigment().getColor().getColorVector() * closestObject->getFinish().getAmbient();
      thisAmbient.x = thisAmbient.x * lightColor.x;
      thisAmbient.y = thisAmbient.y * lightColor.y;
      thisAmbient.z = thisAmbient.z * lightColor.z;
      
      ambient += thisAmbient;
      
      glm::vec3 lightVector = lightSources[i]->getPosition() - ray->getIntersectionPoint();
      lightVector = glm::normalize(lightVector);
      
      if(closestObject->getFinish().getRefraction() > 0.0 && reflectCounter != 0){
	return calculateRefraction(ray, lightSources, collidedObjects, reflectCounter, shader, closestObject, node, planes);
      }       
      
      bool inShadow = isInShadow(ray, lightSources[i], collidedObjects, closestObject,node, planes);
      
      if(inShadow){	
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
	
	specular += calculateSpecular(ray, lightVector, NdotL, closestObject, shader, lightColor);
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
      
      
	theColor = (1.0f - closestObject->getFinish().getReflection()) * theColor + closestObject->getFinish().getReflection() * shade(reflectedRay, lightSources, collidedObjects, reflectCounter - 1, shader, node, planes);

    }   
    
    //theColor.w = closestObject->getPigment().getColor().getColorVector().w;
    
    return theColor;
  }
}

Geometry* findClosestObject(Ray* ray, std::vector<Geometry*> collidedObjects, bvhNode* node, std::vector<Geometry*> planes){
  Geometry* hierarchy = NULL;
  Geometry* plane = NULL;
  Geometry* temp = NULL;
  
  hierarchy = node->intersect(ray, 0.0f, ray->getTime());
  
  for(unsigned int k = 0; k < planes.size(); k++){
    temp = planes[k]->intersect(ray, 0.0f, ray->getTime());
    
    if(temp != NULL){
      plane = temp;
    }
  }
  
  if(plane != NULL){
    return plane;
  }
  else{
    return hierarchy;
  }
}

bool isInShadow(Ray* ray, Light_Source* lightSource, std::vector<Geometry*> collidedObjects, Geometry* closestObject, bvhNode* node, std::vector<Geometry*> planes){

 Ray* shadowFeeler = new Ray();
 shadowFeeler->initializeRay(ray->getIntersectionPoint(), lightSource->getPosition());
            
  Geometry* hierarchy = NULL;
  Geometry* plane = NULL;
  Geometry* temp = NULL;
  
  hierarchy = node->intersect(shadowFeeler, 0.0f, shadowFeeler->getTime());
  
  for(unsigned int k = 0; k < planes.size(); k++){
    temp = planes[k]->intersect(shadowFeeler, 0.0f, shadowFeeler->getTime());
    
    if(temp != NULL){
      plane = temp;
    }
  }
  
  Geometry* toReturn = NULL;
  
  if(plane != NULL){
    toReturn =  plane;
  }
  else{
    toReturn = hierarchy;
  }
  
  if(toReturn == NULL){
    return false;
  }
  
  else if(toReturn->getFinish().getRefraction() != 0.0f){
    return false;
  }  
  
  else{
    return true;
  }
  
  return true;
}

glm::vec4 calculateSpecular(Ray* ray, glm::vec3 lightVector, float NdotL, Geometry* closestObject, int shader, glm::vec4 lightColor){
    glm::vec3 normal = ray->getNormal();
  normal = glm::normalize(normal);
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
	  
	  return thisSpecular;
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
	  
	  return thisSpecular;
	}
	return glm::vec4(0.0f);
}

glm::vec4 calculateRefraction(Ray* ray, std::vector<Light_Source*> lightSources, std::vector<Geometry*> collidedObjects, int reflectCounter, int shader, Geometry* closestObject, bvhNode* node, std::vector<Geometry*> planes){
  glm::vec3 normal = ray->getNormal();
  normal = glm::normalize(normal);
    
  float tempIOR;
  if(ray->getIOR() == closestObject->getFinish().getIor()){
    tempIOR = ray->getIOR();
  }
  else{
    tempIOR = closestObject->getFinish().getIor();
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
	

	  reflectedColor = shade(reflectedRay, lightSources, collidedObjects, (reflectCounter - 1), shader, node, planes);
	
	if(glm::dot(currentRayNormalizedD, normal) <= 0.0f){
	  refract(currentRayNormalizedD, normal, ray->getIOR(), tempIOR, *theT);       
	  c = -1.0f * glm::dot(currentRayNormalizedD, normal);
	}
	
	else{	  
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

	
	glm::vec4 refractedColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	

	  refractedColor = shade(theT, lightSources, collidedObjects, reflectCounter - 1, shader, node, planes);

	return ((R * reflectedColor) + ((1.0f - R) * refractedColor));
	
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
