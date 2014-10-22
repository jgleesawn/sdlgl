#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <CL/opencl.h>

#include "stdio.h"
#include "clengine/clengine.h"
#include "texturemanager/texturemanager.h"
#include "util/sdlutil.h"

class Sprite {
	AtlasLocation location;
	SDL_Rect visRect;
	int tw,th;
	cl_mem clObj;
	int clLoaded;
	
	public:
		Sprite(AtlasLocation, int, CLEngine * cle = NULL);
		~Sprite();
		void NextFrame();
		void DrawOn(SDL_Renderer *, int, int);
		int getWFrame() { return visRect.w; }
		int getHFrame() { return visRect.h; }
		int getFrame() { return visRect.x/visRect.w; }
		SDL_Texture * getTexture() { return TextureManager().getSingleton()->getTexture(location).texture; }
		cl_mem getCL() { return clObj; }
};

#endif
