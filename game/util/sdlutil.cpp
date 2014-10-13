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

