#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <CL/opencl.h>

#include <string>
#include <vector>

#include "clengine.h"
#include "othertypes.h"

class Object;
#include "object.h"



class PhysicsEngine : public CLEngine {
	cl_mem input0,input1;
	cl_mem input4;
public:
	PhysicsEngine(std::string);
	~PhysicsEngine();
	void Init(std::string);

	void Step(Object &);
};

#endif
