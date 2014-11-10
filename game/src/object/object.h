#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Object {
public:
	int index;
	glm::vec4 position;
	Object(glm::vec4);
	void Move(glm::vec4 offset) { position += offset; }
};

class Orientable : public Object {
protected:
//	glm::vec3 verticle;
public:
	glm::quat orientation;
	Orientable(glm::vec4, glm::quat or_in = glm::quat());

	void dQuat(const glm::quat &);
//	void rotParallel(float);
//	void rotPerpendicular(float);

	glm::mat4 getRotMat();
};

void printv(const glm::vec3 &);
void printv(const glm::vec4 &);
void printq(const glm::quat &);
void printm(const glm::mat4 &);
#endif
