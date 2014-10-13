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
		~Sprite();
		void NextFrame();
		void DrawOn(SDL_Renderer *, int, int);
		int getWFrame() { return visRect.w; }
		int getHFrame() { return visRect.h; }
		int getFrame() { return visRect.x/visRect.w; }
		SDL_Texture * getTexture() { return texture; }
};

#endif
