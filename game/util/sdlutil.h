#ifndef SDLUTIL_H
#define SDLUTIL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/glx.h>

#include <string>
#include <iostream>

void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string & file, SDL_Renderer *ren);

struct texProp {
	GLint tid;
	GLenum ttype;
};

texProp getTexId( SDL_Texture * );

#endif
