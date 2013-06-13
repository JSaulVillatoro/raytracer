#ifndef SHADERS_H
#define SHADERS_H

#include "geometry/geometry.h"
#include "core/bvhNode.h"
#include <iostream>

glm::vec4 shade(Ray* ray, std::vector<Light_Source*> lightSources, std::vector<Geometry*> collidedObjects, int reflectCounter, int globalCounter, int shader, bvhNode* node, std::vector<Geometry*> planes);
bool isInShadow(Ray* ray, Light_Source* lightSource, std::vector<Geometry*> collidedObjects, Geometry* closestObject, bvhNode* node, std::vector<Geometry*> planes);
glm::vec4 calculateSpecular(Ray* ray, glm::vec3 lightVector, float NdotL, Geometry* closestObject, int shader, glm::vec4 lightColor);
glm::vec4 calculateRefraction(Ray* ray, std::vector<Light_Source*> lightSources, std::vector<Geometry*> collidedObjects, int reflectCounter, int globalCounter, int shader, Geometry* closestObject, bvhNode* node, std::vector<Geometry*> planes);
bool refract(glm::vec3 d, glm::vec3 n, float prevIOR, float newIOR, Ray &t);
Geometry* findClosestObject(Ray* ray, std::vector<Geometry*> collidedObjects, bvhNode* node, std::vector<Geometry*> planes);
glm::vec3 cosineWeightedDirection(glm::vec3 aNormal);
#endif