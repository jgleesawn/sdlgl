#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "object.h"
#include "glmanager/glmanager.h"

class Renderable : public Orientable {
public:
	gfxObj_t gfxObj;
	Renderable(glm::vec4, gfxObj_t, glm::quat or_in = glm::quat());
};


#endif
