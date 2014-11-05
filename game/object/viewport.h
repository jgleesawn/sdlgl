#ifndef VIEWPORT_H
#define VIEWPORT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>

#include "object.h"

class Viewport : public Orientable {
	float pitch, yaw;
public:
	glm::mat4 perspectiveMatrix;

	Viewport(glm::vec4, glm::vec3 or_in = glm::vec3(0.0f,0.0f,-1.0f), glm::mat4 perspec_in = glm::perspective(glm::radians(45.0f), 1.0f, .1f, 100.0f));
	void Move(glm::vec4);
	void rotParallel(float);
	void rotPerpendicular(float);

	glm::mat4 getRotMat();
};

#endif
