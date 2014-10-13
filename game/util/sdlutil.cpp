#include "sdlutil.h"

void logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string & file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if( texture == nullptr ) {
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

//Associated Gets of glBindTexture
texProp getTexId( SDL_Texture * tex ) {
	GLenum types[8] = {
		GL_TEXTURE_BINDING_1D,
		GL_TEXTURE_BINDING_2D, 
		GL_TEXTURE_BINDING_3D,
		GL_TEXTURE_BINDING_1D_ARRAY,
		GL_TEXTURE_BINDING_2D_ARRAY,
		GL_TEXTURE_BINDING_RECTANGLE,
		GL_TEXTURE_BINDING_2D_MULTISAMPLE,
		GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY };
	GLint ptid[8] = {0,0,0,0,0,0,0,0};
	GLint tid = 0;

	texProp rVal;
	for( int i=0; i<8; i++ ) {
		glGetIntegerv( types[i], &ptid[i] );
	}
	SDL_GL_BindTexture(tex, NULL, NULL);
	for( int i=0; i<8; i++ ) {
		glGetIntegerv( types[i], &tid );
		if( tid != ptid[i] ) {
			glBindTexture( types[i], ptid[i] );
			rVal.tid = tid;
			rVal.ttype = types[i];
			return rVal;	
		}
	}
	rVal.tid = 0;
	rVal.ttype = 0;
	return rVal;
}


