#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "worldengine.h"
#include "object/object.h"

class World {
		WorldEngine we;
		SDL_Renderer * renderer;
		SDL_Texture * rendtex;
		std::vector<Object *> objs;
		int focus;
		int width,height;
	public:
		World(int, int, SDL_Renderer *, CLEngine * cle_in=NULL);
		~World();
		void addObject(Object *);
		void stepSim(int);
		int Size();
		void Show();
};

#endif
