#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Object {
public:
	glm::vec4 position;
	Object(glm::vec4);
	void Move(glm::vec4 offset) { position += offset; }
};

class Orientable : public Object {
protected:
	glm::vec3 verticle;
public:
	glm::vec3 orientation;
	glm::quat rotation;
//	glm::quat orientation;
	Orientable(glm::vec4, glm::vec3 or_in = glm::vec3(0.0f, 0.0f, 1.0f));

	void rotParallel(float);
	void rotPerpendicular(float);
};

void printv(const glm::vec3 &);
void printq(const glm::quat &);
void printm(const glm::mat4 &);
#endif
