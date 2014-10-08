#include "physicsengine.h"

PhysicsEngine::PhysicsEngine(std::string physicsFile, CLEngine * cle_in) { 
	if( cle_in == NULL ) {
		cle = new CLEngine();
		cle_owner = true;
	} else {
		cle = cle_in; 
		cle_owner = false;
	 }
	Init(physicsFile); 
}

PhysicsEngine::~PhysicsEngine() {
	cl_int err;
	while( input.size() != 0 ) {
		while(input.back().size() != 0) {
			err = clReleaseMemObject(input.back().back());
			if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release MemObject."); }
			input.back().pop_back();
		}
		intput.pop_back();
	}
		
	while( !kernels.empty() ) {
		err = clReleaseKernel(kernels.back());
		if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release kernel."); }
		kernels.pop_back();
	}

	err = clReleaseProgram(program);	
	if(err < 0) { fprintf(stderr, "%i\n",err); perror("Couldn't release program."); }

	if( cle_owner )
		delete cle;
}

void PhysicsEngine::Init(std::string physicsFile, std::vector<const char *> kerNames) {
	if( !cle->isInit() )
		cle->Init();
	int err;
	cle->InitializeProgram(physicsFile.c_str(), program);

	for( int i=0; i<kerNames.size(); i++)
		LoadKernel(kerName[i]);
	
	input0 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &err);
	if(err < 0) { perror("Could not create int buffer."); exit(1); }
	input1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &err);
	if(err < 0) { perror("Could not create int buffer."); exit(1); }
}
void PhysicsEngine::LoadKernel(const char * kernelName){
	int err;
	input.push_back(std::vector<cl_mem>);

	kernels.push_back(cl_kernel());
	kernels.back() = clCreateKernel(program, kernelName, &err);
	if(err < 0) { perror("Couldn't create a kernel"); exit(1); }
}

void * PhysicsEngine::getBuffer(int kernel, int input, size_t bytes_s, size_t offset) {
	return cle->getBuffer(input[kernel][input], bytes_s, offset);	
}

