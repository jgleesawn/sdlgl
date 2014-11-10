#ifndef SDLUTIL_H
#define SDLUTIL_H

#include <SDL2/SDL.h>

#include <GL/glx.h>

#include <string>
#include <iostream>

void logSDLError(std::ostream &os, const std::string &msg);

struct TextureProperty {
	GLint tid;
	GLenum ttype;
};

TextureProperty getTexId( SDL_Texture * );

SDL_Rect getSubRect(SDL_Rect, SDL_Rect);

#endif
