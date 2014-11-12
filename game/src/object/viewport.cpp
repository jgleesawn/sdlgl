#include "viewport.h"

Viewport::Viewport(glm::vec4 pos_in, glm::quat or_in, glm::mat4 perspec_in) : Object(pos_in, or_in) {
	perspectiveMatrix = perspec_in;
}

void Viewport::Move(glm::vec4 offset) {
	position -= offset*getRotMat();
}


