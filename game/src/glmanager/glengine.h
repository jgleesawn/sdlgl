#ifndef GLENGINE_H
#define GLENGINE_H

#include <GL/glew.h>

#include "glmanager.h"
#include "basicrenderer.h"
#include "object/viewport.h"
#include "object/renderable.h"
#include "sparseworld/world.h"

class GLEngine {
public:
	GLmanager glm;
	void Render( BasicRenderer *, Renderable *, Viewport * );
	void Render( BasicRenderer *, Renderable *, glm::vec4, Viewport *, glm::vec4 );
	GLEngine() { glewInit(); }
};

#endif
