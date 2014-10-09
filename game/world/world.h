#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "worldengine.h"

class World {
		WorldEngine we;
		sf::RenderTexture rt;
		std::vector<Obj> objs;
		int width,height;
	public:
		World(int, int, CLEngine * cle_in=NULL);
		~World();
		unsigned char * getBuffer();
		void stepSim(int);
		int Size();
};

#endif
