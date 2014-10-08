#ifndef OBJECT_H
#define OBJECT_H

#include <CL/opencl.h>

#include <cstdlib>
#include <vector>
#include <stdio.h>

#include "othertypes.h"

class PhysicsEngine;
#include "physicsengine.h"

class Object {
	PhysicsEngine * pe;
	GLuint positionBufferObject;
	int numItems,width,height;

	void InitializeVertexBuffer();
public:
	Object(PhysicsEngine *,int,int);
	~Object();

	int getNumItems() { return numItems; }
	cl_mem	cl_rgba_mem;

	GLuint getPBO() { return positionBufferObject; }
};

#endif
