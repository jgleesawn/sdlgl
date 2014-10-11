#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include "stdio.h"

class Sprite {
	SDL_Texture *texture;
	SDL_Rect visRect;
	int tw,th;
	
	public:
		Sprite(SDL_Texture *, int);
		void NextFrame();
		void DrawOn(SDL_Renderer *, int, int);
};

#endif
