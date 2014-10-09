#include "worldengine.h"

WorldEngine::WorldEngine(int num,CLEngine * cle_in) : PhysicsEngine("game/world/physics.cl", cle_in) { 
	int err;
	LoadKernel("WorldCompute");

	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_WRITE, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }

}

WorldEngine::~WorldEngine() { }

void WorldEngine::Init(const & sf::Texture texture) {
	GLUint tex_id;
	sf::Texture::Bind(texture);
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &tex_id );

	int err;
	input.back().push_back( clCreateFromGLTexture(cle->getContext(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, tex_id, &err) );
}

void WorldEngine::Step(void * in) {
	int err;

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
	clEnqueueWriteBuffer(cle->getQueue(), input[0][0], CL_FALSE, 0, sizeof(int), &wpos, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][1], CL_FALSE, 0, sizeof(int), &hpos, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][2], CL_FALSE, 0, sizeof(int), &w, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][3], CL_FALSE, 0, sizeof(int), &h, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][4], CL_FALSE, 0, sizeof(int), &mov, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][5], CL_FALSE, 0, sizeof(int), &allowed, 0, NULL, NULL);

	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input[0][0]);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &input[0][1]);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &input[0][2]);
	err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &input[0][3]);
	err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &input[0][4]);
	err |= clSetKernelArg(kernel, 5, sizeof(cl_mem), &input[0][5]);
	err |= clSetKernelArg(kernel, 6, sizeof(cl_mem), &input[0][6]);

	if(err != CL_SUCCESS) { perror("Error setting kernel0 arguments."); }
		
	err = clEnqueueNDRangeKernel(cle->getQueue(), kernel, 1, NULL, &globalNum, &localNum, 0, NULL, NULL);
//	fprintf(stderr,"%i\n",err);
	if(err != CL_SUCCESS) { perror("Error queuing kernel0 for execution."); exit(1); }

	clFinish(cle->getQueue());
}


