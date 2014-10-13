#ifndef CLENGINE_H
#define CLENGINE_H

#include <CL/opencl.h>

#include <GL/glx.h>

#include <string.h>

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>

//#pragma OPENCL EXTENSION cl_khr_gl_sharing : enable

#include "clengine/shader_util.h"
#include "util/sdlutil.h"

class CLEngine {
protected:
	cl_device_id device;
	cl_context context;
	cl_command_queue queue;

	cl_uint	work_group_size;

	void * gl_context;
	bool isInit;
	
public:
	CLEngine();
	~CLEngine();

	void Init();//Required for the glx context functions.
	bool IsInit();
	void InitializeProgram(const char *, cl_program &);

	cl_device_id getDevice() {return device;}
	cl_context getContext() {return context;}
	cl_command_queue getQueue() {return queue;}

	cl_uint getWorkGroupSize() {return work_group_size;}

	void * getBuffer(cl_mem, size_t, size_t);

};


#endif
