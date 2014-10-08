#include "generator.h"

Generator::Generator(int w, int h, CLEngine * cle_in):ge(w*h,cle_in) {
	width = w;
	height = h;
}

Generator::~Generator() { }

unsigned char * Generator::getBuffer() {
	float * buf;
	buf = (float *)ge.getBuffer(0, 2, 4*Size()*sizeof(float), 0);
	unsigned char * Uint8Buf = new unsigned char[4*Size()];
	for( int i=0; i<4*Size(); i++)
		Uint8Buf[i] = (unsigned char)(buf[i]);
	delete buf;
	return Uint8Buf;
}

void Generator::stepSim(int numSteps) {
	for( int i=0; i<numSteps; i++)
		ge.Step(NULL);
}

int Generator::Size(){
	return width*height;
}
