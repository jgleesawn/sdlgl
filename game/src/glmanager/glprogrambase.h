#ifndef GLPROGRAMBASE_H
#define GLPROGRAMBASE_H


#include <string.h>

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>

#include <utility>	//For pair

#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glext.h>
//#include <GL/freeglut.h>

#include "shader_util.h"

typedef std::pair<GLenum,std::string> shaderName;
class GLProgramBase {
protected:
	GLuint theProgram;

	GLuint CreateShader(GLenum, const std::string &);
	GLuint CreateProgram(const std::vector<GLuint> &);
	void   CheckProgram(GLuint &);
public:
	GLuint InitializeProgram(std::vector<shaderName> &);

};


#endif
