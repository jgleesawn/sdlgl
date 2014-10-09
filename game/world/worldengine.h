#ifndef WORLDENGINE_H
#define WORLDENGINE_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <CL/opencl.h>

#include <string>
#include <vector>

#include "clengine/physicsengine.h"

class WorldEngine : public PhysicsEngine {
	int numPixels;
public:
	WorldEngine(CLEngine * cle_in=NULL);
	~WorldEngine();

	void Init(const & sf::Texture);

	void Step(void *);
};

#endif
