#ifndef BASICRENDERER_H
#define BASICRENDERER_H

//#include <GL/glew.h>
#include <string>
#include <vector>


#include "object/renderable.h"
#include "object/viewport.h"
#include "glprogrambase.h"

class BasicRenderer {

	GLuint theProgram;	
	void SetPerspective();

public:
	void Init();

	void Render(Renderable *, Viewport *);

	void reshape(int, int);
};


#endif
