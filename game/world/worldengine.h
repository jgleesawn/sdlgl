#ifndef WORLDENGINE_H
#define WORLDENGINE_H

#include <SDL2/SDL.h>
#include <CL/opencl.h>

#include <string>
#include <vector>

#include "clengine/physicsengine.h"
#include "object/object.h"

struct wePasser {
	SDL_Texture * rendtex;
	Object * obj;
	float movMod;
};

class WorldEngine : public PhysicsEngine {
public:
	WorldEngine(CLEngine * cle_in=NULL);
	~WorldEngine();

	bool Init(SDL_Texture *);

	void addTexture(SDL_Texture *);

	void Step(void *);
};

#endif
