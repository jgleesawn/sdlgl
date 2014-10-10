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
	input.back().push_back( clCreateBuffer(cle->getContext(), CL_MEM_READ_ONLY, sizeof(int), NULL, &err ));
	if( err < 0 ) { perror("Could not create int buffer."); exit(1); }

}

WorldEngine::~WorldEngine() { }

void WorldEngine::Init(const sf::Texture & bgTex) {
	GLint bgTex_id;
	sf::Texture::bind(& bgTex);
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &bgTex_id );

	int err;
	input.back().push_back( clCreateFromGLTexture2D(cle->getContext(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, bgTex_id, &err) );
	if( err < 0 ) { perror("Could not create texture buffer."); exit(1); }
}

void WorldEngine::addTexture(const sf::Texture & newTex) {
	GLint newTex_id;
	sf::Texture::bind(& newTex);
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &newTex_id );

	int err;
	input.back().push_back( clCreateFromGLTexture2D(cle->getContext(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, newTex_id, &err) );
	if( err < 0 ) { perror("Could not create texture buffer."); exit(1); }
}

void WorldEngine::Step(void * in) {
	int err;

	wePasser * wp = (wePasser *) in;
	Animation * anim = wp->anim;
	sf::RenderTexture * rt = wp->rt;
	sf::Vector2i v2 = rt->mapCoordsToPixel(anim->getPosition());
	int wpos = v2.x;
	int hpos = v2.y;
	int w = anim->getWFrame();
	int h = anim->getHFrame();
	int spriteFrame = anim->getFrame();
	float movMod = wp->movMod;
	int bgWidth = rt->getSize().x;

	int wgs = cle->getWorkGroupSize();

	int numPixels = w*h;
	int diff = wgs - numPixels % wgs;
	const size_t osize = numPixels+diff;
	const size_t globalNum = osize;
	size_t localNum = wgs;
	if( osize < wgs )
		localNum = osize;
	const size_t numGroups = (globalNum/localNum)+1;

	//Returns if pointer is null
//	if(input[0][2] == 0) { return; }
	cl_kernel kernel = kernels[0];

//Added input buffers because the commented kernel args would segfault on second loop.
	clEnqueueWriteBuffer(cle->getQueue(), input[0][0], CL_FALSE, 0, sizeof(int), &wpos, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][1], CL_FALSE, 0, sizeof(int), &hpos, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][2], CL_FALSE, 0, sizeof(int), &w, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][3], CL_FALSE, 0, sizeof(int), &h, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][4], CL_FALSE, 0, sizeof(int), &spriteFrame, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][5], CL_FALSE, 0, sizeof(float), &movMod, 0, NULL, NULL);
	clEnqueueWriteBuffer(cle->getQueue(), input[0][6], CL_FALSE, 0, sizeof(int), &bgWidth, 0, NULL, NULL);

	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input[0][0]);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &input[0][1]);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &input[0][2]);
	err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &input[0][3]);
	err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &input[0][4]);
	err |= clSetKernelArg(kernel, 5, sizeof(cl_mem), &input[0][5]);
	err |= clSetKernelArg(kernel, 6, sizeof(cl_mem), &input[0][6]);
	err |= clSetKernelArg(kernel, 7, sizeof(cl_mem), &input[0][7]);
	err |= clSetKernelArg(kernel, 8, sizeof(cl_mem), &input[0][8]);

	err |= clSetKernelArg(kernel, 9, wgs*4*sizeof(float), NULL);
	err |= clSetKernelArg(kernel, 10, numGroups*4*sizeof(float), NULL);

	if(err != CL_SUCCESS) { perror("Error setting kernel0 arguments."); }
		
	err = clEnqueueNDRangeKernel(cle->getQueue(), kernel, 1, NULL, &globalNum, &localNum, 0, NULL, NULL);
//	fprintf(stderr,"%i\n",err);
	if(err != CL_SUCCESS) { perror("Error queuing kernel0 for execution."); exit(1); }

	clFinish(cle->getQueue());

	wp->movMod = movMod;
}


