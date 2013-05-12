#ifndef SHADERS_H
#define SHADERS_H

#include "geometry/geometry.h"
#include <iostream>


glm::vec4 shade(Ray* ray, std::vector<Light_Source*> lightSources, std::vector<Geometry*> collidedObjects, Geometry* closestObject, int reflectCounter, int shader);
bool refract(glm::vec3 d, glm::vec3 n, float prevIOR, float newIOR, Ray &t);
#endif