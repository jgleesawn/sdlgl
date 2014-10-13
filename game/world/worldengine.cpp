#include "worldengine.h"

WorldEngine::WorldEngine(CLEngine * cle_in) : PhysicsEngine("game/world/physics.cl", cle_in) { 
	int err;
	LoadKernel("MovementCompute");

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
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_WRITE, sizeof(float), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
}

WorldEngine::~WorldEngine() { }


//Probably don't need the TEXTUREACCESS_TARGET for access in opencl.
bool WorldEngine::Init(SDL_Texture * bgTex) {
	int accessProp;
	SDL_QueryTexture(bgTex, NULL, &accessProp, NULL, NULL);
	if( accessProp != SDL_TEXTUREACCESS_TARGET )
		return false;

	GLint bgTex_id = getTexId(bgTex).tid;

	//Need to use clCreateFromGLTexture()
	//Then enum in return from getTexId can be used.

	int err;
//	input.back().push_back( clCreateFromGLTexture2D(cle->getContext(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, bgTex_id, &err) );
//	if( err < 0 ) { fprintf(stderr, "%i\n", err); perror("Could not create texture buffer."); exit(1); }
	return true;
}

void WorldEngine::addTexture(SDL_Texture * newTex) {
	GLint newTex_id = getTexId(newTex).tid;
//	glFinish();
//	fprintf(stderr,"%i\n",newTex_id);

	//Need to use clCreateFromGLTexture()
	//Then enum in return from getTexId can be used.

	int err;
//	input.back().push_back( clCreateFromGLTexture2D(cle->getContext(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, newTex_id, &err) );
//	if( err < 0 ) { fprintf(stderr, "%i\n", err); perror("Could not create texture buffer."); exit(1); }
}

void WorldEngine::Step(void * in) {
	glFinish();

	int err;

	wePasser * wp = (wePasser *) in;
	Sprite * spr = wp->obj->curSprite();
	SDL_Texture * rendtex = wp->rendtex;
	int wpos = wp->obj->getX();
	int hpos = wp->obj->getY();
	int w = spr->getWFrame();
	int h = spr->getHFrame();
	int spriteFrame = spr->getFrame();
	float movMod = wp->movMod;

	int wgs = cle->getWorkGroupSize();

	size_t globalNum[2];
	globalNum[0] = w;
	globalNum[1] = h;
	size_t localNum[2];
	localNum[0] = 8;
	localNum[1] = 8;
	if( globalNum[0] < localNum[0] )
		localNum[0] = globalNum[0];
	else
		globalNum[0] += globalNum[0] % 8;
	if( globalNum[1] < localNum[1] )
		localNum[1] = globalNum[1];
	else
		globalNum[1] += globalNum[1] % 8;

//	int numPixels = w*h;
//	int diff = wgs - numPixels % wgs;
//	const size_t osize = numPixels+diff;
//	const size_t globalNum = osize;
//	size_t localNum = wgs;
//	if( osize < wgs )
//		localNum = osize;
	const size_t numGroups = (globalNum[0]/localNum[0])*(globalNum[1]/localNum[1]);

	//Returns if pointer is null
//	if(input[0][2] == 0) { return; }
	cl_kernel kernel = kernels[0];

//Added input buffers because the commented kernel args would segfault on second loop.
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][0], CL_FALSE, 0, sizeof(int), &wpos, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][1], CL_FALSE, 0, sizeof(int), &hpos, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][2], CL_FALSE, 0, sizeof(int), &w, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][3], CL_FALSE, 0, sizeof(int), &h, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][4], CL_FALSE, 0, sizeof(int), &spriteFrame, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][5], CL_FALSE, 0, sizeof(float), &movMod, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing float."); exit(1); }

//	fprintf(stderr, "%i objects in input\n", input[0].size());
	err = clEnqueueAcquireGLObjects(cle->getQueue(), 2, &input[0][6], 0, NULL, NULL);
//	fprintf(stderr,"%i\n", err);
	if(err != CL_SUCCESS) { perror("Error acquiring GL Objects."); exit(1); }
	
	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input[0][0]);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &input[0][1]);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &input[0][2]);
	err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &input[0][3]);
	err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &input[0][4]);
	err |= clSetKernelArg(kernel, 5, sizeof(cl_mem), &input[0][5]);
	err |= clSetKernelArg(kernel, 6, sizeof(cl_mem), &input[0][6]);
	err |= clSetKernelArg(kernel, 7, sizeof(cl_mem), &input[0][7]);

	err |= clSetKernelArg(kernel, 8, localNum[0]*localNum[1]*4*sizeof(int), NULL);
	err |= clSetKernelArg(kernel, 9, numGroups*4*sizeof(int), NULL);

//	fprintf(stderr,"%i\n", err);
	if(err != CL_SUCCESS) { perror("Error setting kernel0 arguments."); exit(1); }
		
	err = clEnqueueNDRangeKernel(cle->getQueue(), kernel, 2, NULL, globalNum, localNum, 0, NULL, NULL);
//	fprintf(stderr,"%i\n",err);
	if(err != CL_SUCCESS) { perror("Error queuing kernel0 for execution."); exit(1); }

	err = clEnqueueReleaseGLObjects(cle->getQueue(), 2, &input[0][6], 0, NULL, NULL);
//	fprintf(stderr,"%i\n", err);
	if(err != CL_SUCCESS) { perror("Error releasing GL Objects."); exit(1); }


	clFinish(cle->getQueue());

	wp->movMod = movMod;
}


