#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "worldengine.h"
#include "object/object.h"

class World {
		WorldEngine we;
		sf::RenderTexture rt;
		std::vector<Object *> objs;
		int focus;
		int width,height;
	public:
		World(int, int, CLEngine * cle_in=NULL);
		~World();
		void addObject(Object *);
		unsigned char * getBuffer();
		void stepSim(int);
		int Size();
		void Show(sf::RenderTarget *);
};

#endif
