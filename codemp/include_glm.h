#ifndef INCLUDE_GLM_H
#define INCLUDE_GLM_H



#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

// from native:
//float data[] = { 1, 2, 3 };
//glm::vec3 vec = glm::make_vec3(data);

// to native:
// glm::vec3 vec(1, 2, 3);
// float* data = glm::value_ptr(vec);

#include "glm/gtc/type_ptr.hpp"

#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective

#endif