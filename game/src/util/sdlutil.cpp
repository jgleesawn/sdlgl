#include "sdlutil.h"

void logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}


//On "No bound texture found." Update texType, bindType, pid and increment listSize.
//Associated Gets of glBindTexture
TextureProperty getTexId( SDL_Texture * tex ) {
#define listSize 9
	GLenum texTypes[listSize] = {
		GL_TEXTURE_1D,
		GL_TEXTURE_2D,
		GL_TEXTURE_3D,
		GL_TEXTURE_RECTANGLE,
		GL_TEXTURE_RECTANGLE_ARB,
		GL_TEXTURE_1D_ARRAY,
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_2D_MULTISAMPLE,
		GL_TEXTURE_2D_MULTISAMPLE_ARRAY };
	GLenum bindTypes[listSize] = {
		GL_TEXTURE_BINDING_1D,
		GL_TEXTURE_BINDING_2D, 
		GL_TEXTURE_BINDING_3D,
		GL_TEXTURE_BINDING_RECTANGLE,
		GL_TEXTURE_BINDING_RECTANGLE_ARB,
		GL_TEXTURE_BINDING_1D_ARRAY,
		GL_TEXTURE_BINDING_2D_ARRAY,
		GL_TEXTURE_BINDING_2D_MULTISAMPLE,
		GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY };
	GLint ptid[listSize] = {0,0,0,0,0,0,0,0,0};
	GLint tid = 0;

	TextureProperty rVal;
	for( int i=0; i<listSize; i++ ) {
		glGetIntegerv( bindTypes[i], &ptid[i] );
		glBindTexture( texTypes[i], 0 );
	}
	SDL_GL_BindTexture(tex, NULL, NULL);
	for( int i=0; i<listSize; i++ ) {
//		fprintf(stderr, "Type: %i\n", bindTypes[i]);
		glGetIntegerv( bindTypes[i], &tid );
		if( tid != 0 ) {
			for( int j=i; j<listSize; j++ )
				glBindTexture( texTypes[j], ptid[j] );
			rVal.tid = tid;
			rVal.ttype = texTypes[i];
			return rVal;	
		}
		glBindTexture( texTypes[i], ptid[i] );
	}
	std::cout << "No bound texture found." << std::endl;
	rVal.tid = 0;
	rVal.ttype = 0;
	return rVal;
#undef listSize
}

SDL_Rect getSubRect(SDL_Rect base, SDL_Rect offset) {
	base.x += offset.x;
	base.y += offset.y;
	base.w = offset.w;
	base.h = offset.h;
	return base;
}
