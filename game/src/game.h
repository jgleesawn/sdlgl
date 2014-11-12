#ifndef GAME_H
#define GAME_H

#include <string>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


#include <vector>

#include "glmanager/glengine.h"
#include "interface/interface.h"

#include "sparseworld/world.h"

class Game {
	
public:
	GLmanager glm;
	BasicRenderer * ren;
	Viewport * view;
	World w;

	std::vector<input> inputs;

	std::vector<gfxObj_t> gfxObjs;
//	std::vector<Renderable *> renObjs;

//	Interface<Viewport> interface;
	Interface<World> interface;

	Game();
	~Game();
	void addInput(const void *, int, int);
	void Loop();
};


#endif



