#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "object.h"
#include "glmanager/glmanager.h"

class Renderable : public Orientable {
public:
	gfxObj_t gfxObj;
	Renderable(glm::vec4, gfxObj_t, glm::vec3 or_in = glm::vec3(0.0f,0.0f,1.0f));
};


#endif
