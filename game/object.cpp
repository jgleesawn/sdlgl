#include "object.h"
//num used to be constant at 1024
Object::Object(PhysicsEngine * pep,int w, int h): width(w), height(h) {
//Velocity buffer.
	numItems = w*h;
	vec4<float> *buf;
	buf = new vec4<float>[numItems];
	memset(buf,0,sizeof(vec4<float>)*numItems);

	pe = pep;

	for( int i=0; i<numItems; i++) {
		for( int j=0; j<3; j++) {
			buf[i].data[j] = rand()%256;
		}
	}
	int err;
	cl_rgba_mem = clCreateBuffer(pe->getContext(), CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 4*sizeof(cl_float)*numItems, buf, &err);
	if(err != CL_SUCCESS) { perror("Couldn't create rgba CLbuffer."); cl_rgba_mem = 0;}
	delete buf;
}
Object::~Object() {
	clReleaseMemObject(cl_rgba_mem);
}

