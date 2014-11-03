#include "glengine.h"

void GLEngine::Render( BasicRenderer * ren, Renderable * obj, Viewport * view ) {
	ren->Render( obj, view );
	glm.Render( obj->gfxObj );
}
