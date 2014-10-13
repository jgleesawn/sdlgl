#include "clengine.h"

CLEngine::CLEngine(): isInit(false) {}
CLEngine::~CLEngine() {
	if( isInit ) {
		cl_int err;
		err = clFinish(queue);
		if(err < 0) { fprintf(stderr,"%i\n",err); perror("Couldn't finish command queue."); }
		err = clReleaseCommandQueue(queue);
		if(err < 0) { fprintf(stderr,"%i\n",err); perror("Couldn't release command queue."); }
		err = clReleaseContext(context);
		if(err < 0) { fprintf(stderr,"%i\n",err); perror("Couldn't release context."); }
	}
}
void CLEngine::Init() {
	int err;
	cl_uint np;
	cl_platform_id platform;
	err = clGetPlatformIDs(1, &platform, &np);
	if(err < 0) { fprintf(stderr,"%i\n",err); perror("Couldn't identify a platform"); exit(1); }

	size_t size;
	char params[500];
	clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, 500,params,&size);
	fprintf(stderr,"%s\n",params);

	
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if(err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
	}
	if(err < 0) { perror("Couldn't access any devices."); exit(1); }

	clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 500,params,&size);
	fprintf(stderr,"%s\n",params);

	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_uint), &work_group_size,&size);
	fprintf(stderr,"Work Group Size: %i\n",work_group_size);
	work_group_size /= 2;

	size_t sizes[40];
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 40*sizeof(size_t), &sizes, &size);
	for( int i=0; i<size/sizeof(size_t); i++) {
		fprintf(stderr,"Work Item Size: %i\n",sizes[i]);
	}

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, 40*sizeof(size_t), &sizes, &size);
	fprintf(stderr, "Global Mem Size: %iB\n",sizes[0]);

	clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, 40*sizeof(size_t), &sizes, &size);
	fprintf(stderr, "Local Mem Size: %iB\n", sizes[0]);
	

//	CONTEXTS ARE DIFFERENT ON DIFFERENT SYSTEMS
//	REQUIRES MORE CODE TO BE COMPATIBLE WITH MACOSX/WINDOWS
//	fprintf(stderr,"gl_context: %i\nglx_context: %i\n", gl_context, glXGetCurrentContext()); 
	cl_context_properties properties[] = 
	{
		CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties) platform,
		0
	};
	context = clCreateContext(properties, 1, &device, NULL, NULL, &err);
	if(err < 0) { perror("Couldn't create a context."); exit(1); }
	fprintf(stderr,"PEC: %i\n", context);

	queue = clCreateCommandQueue(context, device, 0, &err);
	if(err < 0) { perror("Couldn't create a command queue"); exit(1); }

	isInit = true;
}

bool CLEngine::IsInit() {
	return isInit;
}

void CLEngine::InitializeProgram(const char * filename, cl_program & program) {
	int err;
	std::string progData = getFile(filename);

	size_t size = progData.size();

	const char * data_cstr = progData.c_str();	
	program = clCreateProgramWithSource(context, 1, &data_cstr, &size, &err);
	if(err < 0) { perror("Couldn't create the program."); exit(1); }
	
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if(err < 0) {
		size_t log_size;
		char * log;
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = new char[log_size];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size+1, log, NULL);
		fprintf(stderr, "%s\n", log);
		delete log;
		exit(1);
	}
}

void * CLEngine::getBuffer(cl_mem clptr, size_t bytes, size_t offset=0 ) {
	cl_int err;
	cl_event event;

	void * buf;
	buf = new unsigned char[bytes];
	err = clEnqueueReadBuffer(queue, clptr, CL_TRUE, offset, bytes, buf,0, NULL, &event);
	clWaitForEvents(1, &event);

//	printf("%p\n",buf);
	if(err < 0) { perror("Couldn't read buffer."); }
	return buf;
}
