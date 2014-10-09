#include "generatorengine.h"

GeneratorEngine::GeneratorEngine(int num,CLEngine * cle_in) : PhysicsEngine("game/generator/physics.cl", cle_in) { 
	int err;
	numPixels = num;
	LoadKernel("pixelInteract");

	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }

	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_WRITE, 4*sizeof(cl_float)*numPixels, NULL, &err));
	if( err < 0 ) { perror("Could not create vec4<float> buffer."); exit(1); }

	float * buf = new float[4*numPixels];
	for( int i=0; i<4*numPixels; i++)
		buf[i] = rand()%256;
	clEnqueueWriteBuffer(cle->getQueue(), input[0][2], CL_TRUE, 0, 4*numPixels*sizeof(cl_float), buf, 0, NULL, NULL);
	delete buf;
	
}

GeneratorEngine::~GeneratorEngine() { }

void GeneratorEngine::Step(void * in) {
	int err;

	cl_event events[2];

	int wgs = cle->getWorkGroupSize();

	int diff = wgs - numPixels % wgs;
	const size_t osize = numPixels+diff;
	const size_t globalNum = osize;
	size_t localNum = wgs;
	if( osize < wgs )
		localNum = osize;
	const size_t numGroups = (globalNum/localNum)+1;

	//Returns if pointer is null
	if(input[0][2] == 0) { return; }
	cl_kernel kernel = kernels[0];

	int width,height;
//Added input buffers because the commented kernel args would segfault on second loop.
	clEnqueueWriteBuffer(cle->getQueue(), input[0][0], CL_FALSE, 0, sizeof(int), &width, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][1], CL_FALSE, 0, sizeof(int), &height, 0, NULL, NULL);
	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input[0][0]);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &input[0][1]);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &input[0][2]);

	if(err != CL_SUCCESS) { perror("Error setting kernel0 arguments."); }
		
	err = clEnqueueNDRangeKernel(cle->getQueue(), kernel, 1, NULL, &globalNum, &localNum, 0, NULL, NULL);
//	fprintf(stderr,"%i\n",err);
	if(err != CL_SUCCESS) { perror("Error queuing kernel2 for execution."); exit(1); }

	clFinish(cle->getQueue());
}


