#include "viewport.h"

Viewport::Viewport(glm::vec4 pos_in, glm::vec3 or_in, glm::mat4 perspec_in) : Orientable(pos_in, or_in) {
	perspectiveMatrix = perspec_in;
	pitch = 0.0f;
	yaw = 0.0f;
}

void Viewport::Move(glm::vec4 offset) {
	position -= offset*getRotMat();
}

void Viewport::rotParallel(float rad) {
	yaw += rad;
}

void Viewport::rotPerpendicular(float rad) {
	pitch += rad;
}

glm::mat4 Viewport::getRotMat() {
	//return glm::eulerAngleYX(yaw, pitch);
	return glm::eulerAngleXY(pitch, yaw);
}


