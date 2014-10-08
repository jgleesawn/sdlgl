#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <CL/opencl.h>

#include <string>
#include <vector>

#include "clengine.h"
//#include "util/othertypes.h"


class PhysicsEngine {
protected:
	CLEngine * cle;

	cl_program program;
	std::vector<cl_kernel> kernels;
	std::vector<std::vector<cl_mem> > input;

	bool cle_owner;
public:
	PhysicsEngine(std::string physicsFile, CLEngine * cle_in=NULL);
	~PhysicsEngine();

	CLEngine * getCLEngine() { return cle; }

	void Init(std::string, std::vector<const char *>);
	void LoadKernel(const char *);

	unsigned char * getBuffer(int, int, size_t, size_t);

	virtual void Step(void *);
};

#endif
