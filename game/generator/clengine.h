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

#include "shader_util.h"

class CLEngine {
protected:
	cl_device_id device;
	cl_context context;
	cl_program program;
	std::vector<cl_kernel> kernels;
	cl_command_queue queue;

	cl_uint	work_group_size;

	void * gl_context;
	
	void _init();//Required for the glx context functions.
	void InitializeProgram(const char *);
public:
	CLEngine();
	~CLEngine();
	cl_context getContext() {return context;}

	void * getBuffer(cl_mem, size_t, size_t);

};


#endif
