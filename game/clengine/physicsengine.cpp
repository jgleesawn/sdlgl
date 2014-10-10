#include "physicsengine.h"

PhysicsEngine::PhysicsEngine(const char * physicsFile, CLEngine * cle_in) { 
	if( cle_in == NULL ) {
		cle = new CLEngine();
		cle_owner = true;
	} else {
		cle = cle_in; 
		cle_owner = false;
	 }
	if( !cle->IsInit() )
		cle->Init();
	cle->InitializeProgram(physicsFile, program);
}

PhysicsEngine::~PhysicsEngine() {
	fprintf(stderr, "Physics Destructor.\n");
	cl_int err;
	while( input.size() != 0 ) {
//		fprintf(stderr, "%i\n", input.size());
		while(input.back().size() != 0) {
//			fprintf(stderr, "%i\n", input.back().size());
			err = clReleaseMemObject(input.back().back());
			if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release MemObject."); }
			input.back().pop_back();
		}
		input.pop_back();
	}
		
	while( !kernels.empty() ) {
//		fprintf(stderr, "%i\n", kernels.size());
		err = clReleaseKernel(kernels.back());
		fprintf(stderr,"%i\n",err);
		if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release kernel."); }
		kernels.pop_back();
	}

	err = clReleaseProgram(program);	
	if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release program."); }

	if( cle_owner )
		delete cle;
}

void PhysicsEngine::LoadKernel(const char * kernelName){
	int err;
	input.push_back(std::vector<cl_mem>());

	kernels.push_back(cl_kernel());
	kernels.back() = clCreateKernel(program, kernelName, &err);
	if(err < 0) { perror("Couldn't create a kernel"); exit(1); }
}

void * PhysicsEngine::getBuffer(int kernel, int buf, size_t bytes_s, size_t offset) {
	return cle->getBuffer(input[kernel][buf], bytes_s, offset);	
}

