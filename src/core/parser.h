#ifndef PARSER_H
#define PARSER_H

#include <../third_party/glm/glm.hpp>

bool isComment(std::ifstream& fin);
int setVector(std::ifstream& fin, glm::vec3& vector);
int setVector4(std::ifstream& fin, glm::vec4& vector);
#endif
