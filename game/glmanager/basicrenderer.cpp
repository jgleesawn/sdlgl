#include "basicrenderer.h"

//Need Init function so that the GL context is set up already;
//VE is created before GL context is set up.
BasicRenderer::BasicRenderer() {
	std::vector<shaderName> shaderNames;
	shaderNames.push_back(shaderName(GL_VERTEX_SHADER, std::string("renderers/basic.v.shader")));
//	shaderNames.push_back(shaderName(GL_GEOMETRY_SHADER, std::string("renderers/basic.g.shader")));
	shaderNames.push_back(shaderName(GL_FRAGMENT_SHADER, std::string("renderers/basic.f.shader")));

	theProgram = GLProgramBase().InitializeProgram(shaderNames);

	std::cout << theProgram << std::endl;

	glUseProgram(theProgram);
//	GLint uvar[5];
	uvar[0] = glGetUniformLocation( theProgram, "objPosition");
	uvar[1] = glGetUniformLocation( theProgram, "objRotation");
	uvar[2] = glGetUniformLocation( theProgram, "viewOffset");
	uvar[3] = glGetUniformLocation( theProgram, "viewRotation");
	uvar[4] = glGetUniformLocation( theProgram, "Perspective");

	for( int i=0; i<5; i++ )
		std::cout << uvar[i] << std::endl;
	glUseProgram(0);
}

//Transpose = GL_TRUE because GLSL uses Column-Major where C++ typicall uses Row-Major
void BasicRenderer::Render( Renderable * objs, Viewport * view ) {
	glUseProgram(theProgram);
	glUniform4f(uvar[0], objs->position[0], objs->position[1], objs->position[2], 0.0f);
	glUniformMatrix4fv(uvar[1], 1, GL_TRUE, &objs->rotationMatrix[0][0]);
	glUniform4f(uvar[2], view->pos[0], view->pos[1], view->pos[2], 0.0f);
	glUniformMatrix4fv(uvar[3], 1, GL_TRUE, &view->rotationMatrix[0][0]);
	glUniformMatrix4fv(uvar[4], 1, GL_TRUE, &view->perspectiveMatrix[0][0]);
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

