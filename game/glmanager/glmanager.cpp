#inclue "glmanager.h"

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

//vbos are updated(DYNAMIC)
//ibos are not(STATIC)
bool GLmanager::Load( std::vector< std::vector<float> * > * vbos_in, std::vector< std::vector<int> * > * ibos_in ) {
	if( vbos_in->size() != ibos_in->size() )
		return false;

	int vbo_size = 0;
	int ibo_size = 0;
	for( int i=0; i<vbos_in->size(); i++ ) {
		vbo_size += vbos_in->at(i)->size();
		ibo_size += ibos_in->at(i)->size();
	}

	ObjGroupr * gfxObj = new ObjGroup;

	gfxObj->vbo_struct_size = sizeof(*vbos_in->at(0)->data());
	gfxObj->ibo_struct_size = sizeof(*ibos_in->at(0)->data());
	
	glGenBuffers(1, &gfxObj->VBO);
	glBindBuffer( GL_ARRAY_BUFFER, &gfxObj->VBO);
	glBufferData( GL_ARRAY_BUFFER, vbo_size * gfxObj->vbo_struct_size, NULL, GL_DYNAMIC_DRAW);
		
	glGenBuffers(1, &gfxObjs->IBO);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, &gfxObj->IBO);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, ibo_size * gfxObj->ibo_struct_size, NULL, GL_STATIC_DRAW);

	glGenVertexArrays(1, &gfxObjs->VAO);
	glBindVertexArray(&gfxObjs->VAO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, gfxObj->vbo_struct_size, (void*) 0);
	glEnableVertexAtrribArray(0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, &gfxObj->IBO);

	int vbo_offset, ibo_offset;
	vbo_offset = ibo_offset = 0;	
	for( int i=0; i<vbos_in->size(); i++ ) {
		gfxObj->VBOStartingIndices.push_back(vbo_offset);
		gfxObj->IBOStartingIndices.push_back(ibo_offset);
		glBufferSubData( GL_ARRAY_BUFFER, vbo_offset*gfxObj->vbo_struct_size, vbos_in->at(i)->size()*gfxObj->vbo_struct_size, vbos_in->at(i)->data() );
		vbo_offset += vbos_in->at(i)->size();
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, ibo_offset*gfxObj->ibo_struct_size, ibos_in->at(9)->size()*gfxObj->ibo_struct_size, ibos_in->at(i)->data() );
		ibo_offset += ibos_in->at(i)->size();
	}
	gfxObj->VBOStartingIndices.push_back(vbo_offset);
	gfxObj->IBOStartingIndices.push_back(ibo_offset);
	gfxObjs.push_back(gfxObj);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, 0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Render(gfxObjID goID, vec4<float> position, vec4<float> rotation) {
	GLuint vao = gfxObjs.at(goID.vao)->VAO;
	int ind = goID.ind;
	
	glBindVertexArray(vao);

	int count = gfxObjs.at(goID.vao)->IBOStartingIndices.at(goID.ind+1) - gfxObjs.at(goID.vao)->IBOStartingIndices.at(goID.ind);
	int indoffset = gfxObjs.at(goID.vao)->IBOStartingIndices.at(goID.ind) * gfxObjs.at(goID.vao)->ibo_struct_size;
	int baseoffset = gfxObjs.at(goID.vao)->VBOStartingIndices.at(goID.ind);
	glDrawElementsBaseVertex( GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)indoffset, baseoffset);
}




