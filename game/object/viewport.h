#ifndef VIEWPORT_H
#define VIEWPORT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

class Viewport {
public:
	glm::vec4 pos;
	glm::mat4 rotationMatrix;
	glm::mat4 perspectiveMatrix;

	Viewport(glm::vec4, glm::mat4 rot_in = glm::mat4(), glm::mat4 perspec_in = glm::perspective(glm::radians(45.0f), 1.0f, .1f, 100.0f));
};

#endif
