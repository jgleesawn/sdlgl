#include "basicrenderer.h"

//Need Init function so that the GL context is set up already;
//VE is created before GL context is set up.
void BasicRenderer::Init() {
	std::vector<shaderName> shaderNames;
	shaderNames.push_back(shaderName(GL_VERTEX_SHADER, std::string("renderers/basic.v.shader")));
//	shaderNames.push_back(shaderName(GL_GEOMETRY_SHADER, std::string("renderers/basic.g.shader")));
	shaderNames.push_back(shaderName(GL_FRAGMENT_SHADER, std::string("renderers/basic.f.shader")));

	theProgram = GLProgramBase().InitializeProgram(shaderNames);

	SetPerspective();

	glUseProgram(theProgram);
	glUseProgram(0);
}

void BasicRenderer::SetPerspective() {
	float fFrustumScale = 1.0; float fzNear = 0.1f; float fzFar = 100000.0f;
	
	float theMatrix[16];
	memset(theMatrix, 0, sizeof(float) * 16);
	
	theMatrix[0] = fFrustumScale;
	theMatrix[5] = fFrustumScale;
	theMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
	theMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
	theMatrix[11] = -1.0f;
	
	glUseProgram(theProgram);
	glUniformMatrix4fv(4, 1, GL_FALSE, theMatrix);
	glUseProgram(0);
}

void BasicRenderer::Render( Renderable * objs, Viewport * view ) {
	glUseProgram(theProgram);
	glUniform4f(0, objs->position[0], objs->position[1], objs->position[2], 0.0f);
	glUniformMatrix4fv(1, 1, GL_FALSE, &objs->rotationMatrix[0][0]);
	glUniform4f(2, view->pos[0], view->pos[1], view->pos[2], 0.0f);
	glUniformMatrix4fv(3, 1, GL_FALSE, &view->rotationMatrix[0][0]);
	glUniformMatrix4fv(4, 1, GL_FALSE, &view->perspectiveMatrix[0][0]);
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

