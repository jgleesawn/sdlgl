#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <GL/gl.h>
#include <vector>

#include "util/othertypes.h"

struct gfxObjID {
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
	bool Load(std::vector<std::vector<vec4<float> > * > * vbos_in, std::vector< std::vector<int> * > * ibos_in)
	void Update(gfxObjID, std::vector<float>);
	void Render(gfxObjID, vec4<float>, float[16]);
};

#endif
