#ifndef GLENGINE_H
#define GLENGINE_H

#include <GL/glew.h>

#include "glmanager.h"
#include "basicrenderer.h"
#include "object/viewport.h"
#include "object/renderable.h"

class GLEngine {
public:
	GLmanager glm;
	void Render( BasicRenderer *, Renderable *, Viewport * );
	GLEngine() { glewInit(); }
};

#endif
