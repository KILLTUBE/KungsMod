#ifndef PRIMITIVES_3D_H
#define PRIMITIVES_3D_H

#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective


void kung_cube(float *data, float x, float y, float z, glm::mat4x4 mat);

#endif