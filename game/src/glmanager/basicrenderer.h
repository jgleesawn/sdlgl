#ifndef BASICRENDERER_H
#define BASICRENDERER_H

//#include <GL/glew.h>
#include <string>
#include <vector>

#include <iostream>

#include "object/renderable.h"
#include "object/viewport.h"
#include "glprogrambase.h"

//May have to change Render function to virtual.

class BasicRenderer {

	GLuint theProgram;
	GLint uvar[5];	//Uniform variables used because #120 doesn't support explicit locations
public:
	BasicRenderer();
	~BasicRenderer() { glDeleteProgram(theProgram); }

	void Render(Renderable *, Viewport *);
	void Render(Renderable *, glm::vec4, Viewport *, glm::vec4);

	void reshape(int, int);
};


#endif
