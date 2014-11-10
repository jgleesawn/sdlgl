#include "glengine.h"

void GLEngine::Render( BasicRenderer * ren, Renderable * obj, Viewport * view ) {
	ren->Render( obj, view );
	glm.Render( obj->gfxObj );
}

void GLEngine::Render( BasicRenderer * ren, Renderable * obj, glm::vec4 opos, Viewport * view, glm::vec4 vpos ) {
	ren->Render( obj, opos, view, vpos );
	glm.Render( obj->gfxObj );
}

