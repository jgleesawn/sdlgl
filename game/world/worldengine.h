#ifndef WORLDENGINE_H
#define WORLDENGINE_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <CL/opencl.h>

#include <string>
#include <vector>

#include "clengine/physicsengine.h"
#include "object/animation.h"

struct wePasser {
	sf::RenderTexture * rt;
	Animation * anim;
	float movMod;
};

class WorldEngine : public PhysicsEngine {
public:
	WorldEngine(CLEngine * cle_in=NULL);
	~WorldEngine();

	void Init(const sf::Texture &);

	void addTexture(const sf::Texture &);

	void Step(void *);
};

#endif
