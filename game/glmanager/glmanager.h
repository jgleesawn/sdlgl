#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <GL/glew.h>
//#include <GL/gl.h>
//#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <utility>
#include <iostream>

#include "objmodel.h"
#include "objloader.h"

struct gfxObj_t {
	int vao;
	int ind;
};

struct ObjGroup {
	GLuint VBO;
	GLuint IBO;
	GLuint VAO;
	size_t vbo_struct_size;
	size_t ibo_struct_size;
	std::vector<int> IBOStartingIndices;
	std::vector<int> VBOStartingIndices;
};


class GLmanager {
	std::vector<ObjGroup *> gfxObjs;

public:
	~GLmanager();
	std::vector<gfxObj_t> Load(const std::vector< objModel > & vobj );//std::vector<std::vector<glm::vec4 > * > * vbos_in, std::vector< std::vector<int> * > * ibos_in);
	std::vector<gfxObj_t> Load(const std::vector< std::string > & );
	void Update(gfxObj_t, std::vector<float>);
	void Render(gfxObj_t);
};

#endif
