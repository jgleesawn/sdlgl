#include "worldengine.h"

WorldEngine::WorldEngine(CLEngine * cle_in) : PhysicsEngine("game/world/physics.cl", cle_in) { 
	int err;
	LoadKernel("MovementCompute");

	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(cl_int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(cl_int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(cl_int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(cl_int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(cl_int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(cl_int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(cl_int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_WRITE, sizeof(cl_float), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }
}

WorldEngine::~WorldEngine() { }


//Probably don't need the TEXTUREACCESS_TARGET for access in opencl.
bool WorldEngine::Init(SDL_Texture * bgTex) {
//	TextureLocation tl;
//	tl = TextureManager().getSingleton()->getTexture(al);
	Uint32 fmt;
	int acc;
	SDL_QueryTexture(bgTex, &fmt, &acc, NULL, NULL);
//	fprintf(stderr, "fmt: %u\nacc: %i\n", fmt, acc);

//Makes sure init texture can be used for rendering by SDL.
	if( acc != SDL_TEXTUREACCESS_TARGET )
		return false;

	TextureProperty tp = getTexId(bgTex);

//	fprintf(stderr, "tid: %i\nttype: %i\n", tp.tid, tp.ttype );
	//Need to use clCreateFromGLTexture()
	//Then enum in return from getTexId can be used.

	int err;
	input.back().push_back( clCreateFromGLTexture2D(cle->getContext(), CL_MEM_READ_WRITE, tp.ttype, 0, tp.tid, &err) );
	if( err < 0 ) { fprintf(stderr, "%i\n", err); perror("Could not create texture buffer."); exit(1); }
	return true;
}

void WorldEngine::addTexture(SDL_Texture * newTex) {
	TextureProperty tp = getTexId(newTex);
//	fprintf(stderr, "tid: %i\nttype: %i\n", tp.tid, tp.ttype );

//	printf("addTex\n");
	int err;
	input.back().push_back( clCreateFromGLTexture2D(cle->getContext(), CL_MEM_READ_WRITE, tp.ttype, 0, tp.tid, &err) );
	if( err < 0 ) { fprintf(stderr, "%i\n", err); perror("Could not create texture buffer."); exit(1); }
//	printf("addTex\n");
}

void WorldEngine::Step(void * in) {
	glFinish();

	int err;

	wePasser * wp = (wePasser *) in;
	Sprite * spr = wp->obj->curSprite();
	TextureLocation tl = spr->getTextureLocation();

	SDL_Texture * rendtex = wp->rendtex;
	int wpos = wp->obj->getX();
	int hpos = wp->obj->getY();
	int w = spr->getWFrame();
	int h = spr->getHFrame();
	int srcx = tl.lrect.x;
	int srcy = tl.lrect.y;
	int spriteFrame = spr->getFrame();
	float movMod = wp->movMod;

	cl_mem sprCL = spr->getCL();

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

	const size_t numGroups = (globalNum[0]/localNum[0])*(globalNum[1]/localNum[1]);

	cl_kernel kernel = kernels[0];

	cl_mem commBuf = clCreateBuffer( cle->getContext(), CL_MEM_READ_WRITE, 4*sizeof(cl_float)*numGroups, NULL, &err);
	if(err != CL_SUCCESS) { perror("Error creating commBuf."); fprintf(stderr, "%i\n", err); exit(1); }

//Added input buffers because the commented kernel args would segfault on second loop.
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][0], CL_FALSE, 0, sizeof(cl_int), &wpos, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][1], CL_FALSE, 0, sizeof(cl_int), &hpos, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][2], CL_FALSE, 0, sizeof(cl_int), &w, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][3], CL_FALSE, 0, sizeof(cl_int), &h, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][4], CL_FALSE, 0, sizeof(cl_int), &srcx, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][5], CL_FALSE, 0, sizeof(cl_int), &srcy, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][6], CL_FALSE, 0, sizeof(cl_int), &spriteFrame, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing int."); exit(1); }
	err = clEnqueueWriteBuffer(cle->getQueue(), input[0][7], CL_FALSE, 0, sizeof(cl_float), &movMod, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error writing float."); exit(1); }

//	fprintf(stderr, "%i objects in input\n", input[0].size());
//fprintf(stderr,"rendtex");
	err = clEnqueueAcquireGLObjects(cle->getQueue(), 1, &input[0][8], 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error acquiring GL Objects."); exit(1); }
//fprintf(stderr,"obj[focus]: %i\n", sprCL);
	err = clEnqueueAcquireGLObjects(cle->getQueue(), 1, &sprCL, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error acquiring GL Objects."); exit(1); }

	
	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input[0][0]);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &input[0][1]);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &input[0][2]);
	err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &input[0][3]);
	err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &input[0][4]);
	err |= clSetKernelArg(kernel, 5, sizeof(cl_mem), &input[0][5]);
	err |= clSetKernelArg(kernel, 6, sizeof(cl_mem), &input[0][6]);
	err |= clSetKernelArg(kernel, 7, sizeof(cl_mem), &input[0][7]);
	err |= clSetKernelArg(kernel, 8, sizeof(cl_mem), &input[0][8]);
	err |= clSetKernelArg(kernel, 9, sizeof(cl_mem), &sprCL);

	err |= clSetKernelArg(kernel, 10, localNum[0]*localNum[1]*4*sizeof(cl_float), NULL);
	err |= clSetKernelArg(kernel, 11, sizeof(cl_mem), &commBuf);

	if(err != CL_SUCCESS) { perror("Error setting kernel0 arguments."); fprintf(stderr, "%i\n", err); exit(1); }
		
	err = clEnqueueNDRangeKernel(cle->getQueue(), kernel, 2, NULL, globalNum, localNum, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error queuing kernel0 for execution."); fprintf(stderr, "%i\n", err); exit(1); }

	err = clEnqueueReadBuffer(cle->getQueue(), input[0][7], CL_FALSE, 0, sizeof(cl_float), &movMod, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error reading CL's movMod."); fprintf(stderr, "%i\n", err); exit(1); }

	err = clEnqueueReleaseGLObjects(cle->getQueue(), 1, &input[0][8], 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error releasing GL Objects."); fprintf(stderr, "%i\n", err); exit(1); }
	err = clEnqueueReleaseGLObjects(cle->getQueue(), 1, &sprCL, 0, NULL, NULL);
	if(err != CL_SUCCESS) { perror("Error releasing GL Objects."); fprintf(stderr, "%i\n", err); exit(1); }


	clFinish(cle->getQueue());
	clReleaseMemObject(commBuf);

	wp->movMod = movMod;
}


