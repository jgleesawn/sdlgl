#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "object.h"
#include "glmanager/glmanager.h"

class Renderable : public Object {
public:
	gfxObj_t gfxObj;
	glm::mat4 rotationMatrix;
	Renderable(glm::vec4, gfxObj_t, glm::mat4 rot_in = glm::mat4(1.0f));
};


#endif
