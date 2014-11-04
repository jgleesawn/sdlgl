#ifndef BASICRENDERER_H
#define BASICRENDERER_H

//#include <GL/glew.h>
#include <string>
#include <vector>

#include <iostream>

#include "object/renderable.h"
#include "object/viewport.h"
#include "glprogrambase.h"

class BasicRenderer {

	GLuint theProgram;
	GLint uvar[5];	//Uniform variables used because #120 doesn't support explicit locations
public:
	BasicRenderer();
	~BasicRenderer() { glDeleteProgram(theProgram); }

	void Render(Renderable *, Viewport *);

	void reshape(int, int);
};


#endif
