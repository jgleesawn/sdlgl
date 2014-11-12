#include "glmanager.h"

GLmanager::~GLmanager() {
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, 0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);

	while( !gfxObjs.empty() ) {
		glDeleteBuffers(1, &gfxObjs.back()->VBO);
		glDeleteBuffers(1, &gfxObjs.back()->IBO);
		glDeleteVertexArrays(1, &gfxObjs.back()->VAO);

		delete gfxObjs.back();
		gfxObjs.pop_back();
	}
}

//vbos are updated	(DYNAMIC)
//ibos are not		(STATIC)
std::vector<gfxObj_t> GLmanager::Load( const std::vector< objModel > & vobj ) {
	std::vector<gfxObj_t> out;
	if( vobj.empty() )
		return out;

	int vbo_size = 0;
	int ibo_size = 0;
	for( int i=0; i<vobj.size(); i++ ) {
		vbo_size += vobj[i].vertices.size();
		ibo_size += vobj[i].indices.size();
	}

	ObjGroup * og = new ObjGroup;

	og->vbo_struct_size = sizeof(*vobj[0].vertices.data());
	og->ibo_struct_size = sizeof(*vobj[0].indices.data());
	
	glGenBuffers(1, &og->VBO);
	glBindBuffer( GL_ARRAY_BUFFER, og->VBO);
	glBufferData( GL_ARRAY_BUFFER, vbo_size * og->vbo_struct_size, NULL, GL_DYNAMIC_DRAW);
		
	glGenBuffers(1, &og->IBO);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, og->IBO);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, ibo_size * og->ibo_struct_size, NULL, GL_STATIC_DRAW);

	glGenVertexArrays(1, &og->VAO);
	glBindVertexArray(og->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, og->vbo_struct_size, (void*) 0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, og->IBO);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

	int vbo_offset, ibo_offset;
	vbo_offset = ibo_offset = 0;	

	for( int i=0; i<vobj.size(); i++ ) {
		gfxObj_t go = {(int)gfxObjs.size(), i};
		out.push_back(go);

		og->VBOStartingIndices.push_back(vbo_offset);
		og->IBOStartingIndices.push_back(ibo_offset);
		glBufferSubData( GL_ARRAY_BUFFER, vbo_offset*og->vbo_struct_size, vobj[i].vertices.size()*og->vbo_struct_size, vobj[i].vertices.data() );
		vbo_offset += vobj[i].vertices.size();
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, ibo_offset*og->ibo_struct_size, vobj[i].indices.size()*og->ibo_struct_size, vobj[i].indices.data() );
		ibo_offset += vobj[i].indices.size();
	}
//	std::cout << vbo_offset << std::endl << ibo_offset << std::endl;
	og->VBOStartingIndices.push_back(vbo_offset);
	og->IBOStartingIndices.push_back(ibo_offset);

	gfxObjs.push_back(og);

	glBindBuffer( GL_ARRAY_BUFFER, 0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);

	return out;
}

std::vector<gfxObj_t> GLmanager::Load(const std::vector< std::string > & fileNames ) {
	std::vector<objModel> vobj;
	for( int i=0; i<fileNames.size(); i++ )
		vobj.push_back(std::move(loadObjFile(fileNames[i])));
	return Load(vobj);
}


