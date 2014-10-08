#include "physicsengine.h"

PhysicsEngine::PhysicsEngine(std::string physicsFile) : CLEngine() { 
	Init(physicsFile); 
}

PhysicsEngine::~PhysicsEngine() {
	cl_int err;
	err = clReleaseMemObject(input1);
	err = clReleaseMemObject(input0);
	while( !kernels.empty() ) {
		err = clReleaseKernel(kernels.back());
		if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release kernel."); }
		kernels.pop_back();
	}
	err = clReleaseCommandQueue(queue);
	if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release command queue."); }
}

void PhysicsEngine::Init(std::string physicsFile) {
	_init();

	int err;
	InitializeProgram(physicsFile.c_str());
	
	queue = clCreateCommandQueue(context, device, 0, &err);
	if(err < 0) { perror("Couldn't create a command queue"); exit(1); }

	kernels.push_back(cl_kernel());
	kernels[0] = clCreateKernel(program, "updateVelocity", &err);
	if(err < 0) { perror("Couldn't create a kernel"); exit(1); }	

	kernels.push_back(cl_kernel());
	kernels[1] = clCreateKernel(program, "applyVelocity", &err);
	if(err < 0) { perror("Couldn't create a kernel"); exit(1); }

	kernels.push_back(cl_kernel());
	kernels[2] = clCreateKernel(program, "pixelInteract", &err);
	if(err < 0) { perror("Couldn't create a kernel"); exit(1); }

	input0 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &err);
	if(err < 0) { perror("Could not create int buffer."); exit(1); }
	input1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &err);
	if(err < 0) { perror("Could not create int buffer."); exit(1); }
}

void PhysicsEngine::Step(Object & obj) {
	int err;

	cl_event events[2];

	int diff = work_group_size - obj.getNumItems()%work_group_size;
	const size_t osize = obj.getNumItems()+diff;
	const size_t globalNum = osize;
	size_t localNum = work_group_size;
	if( osize < work_group_size )
		localNum = osize;
	const size_t numGroups = (globalNum/localNum)+1;

	//Returns if pointer is null
	if(obj.cl_rgba_mem == 0) { return; }
	cl_kernel kernel = kernels[2];

	int width,height;
//Added input buffers because the commented kernel args would segfault on second loop.
	clEnqueueWriteBuffer(queue, input0, CL_FALSE, 0, sizeof(int), &width, 0, NULL, NULL);
	clEnqueueWriteBuffer(queue, input1, CL_FALSE, 0, sizeof(int), &height, 0, NULL, NULL);
	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input0);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &input1);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &obj.cl_rgba_mem);

	if(err != CL_SUCCESS) { perror("Error setting kernel0 arguments."); }
		
	err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalNum, &localNum, 0, NULL, NULL);
//	fprintf(stderr,"%i\n",err);
	if(err != CL_SUCCESS) { perror("Error queuing kernel2 for execution."); exit(1); }

	clFinish(queue);
}


