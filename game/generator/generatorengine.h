#ifndef GENERATORENGINE_H
#define GENERATORENGINE_H

#include <CL/opencl.h>

#include <string>
#include <vector>

#include "clengine/physicsengine.h"



class GeneratorEngine : public PhysicsEngine {
	int numPixels;
public:
	GeneratorEngine(int numPixels, CLEngine * cle_in=NULL);
	~GeneratorEngine();

	void Step(void *);
};

#endif
