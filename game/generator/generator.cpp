#include "generator.h"

Generator::Generator(int w, int h) {
	width = w;
	height = h;
	pe = new PhysicsEngine("game/generator/physics.cl");
	obj = new Object(pe, width, height);
}

Generator::~Generator() {
	delete pe;
	delete obj;
}

unsigned char * Generator::getBuffer() {
	float * buf;
	buf = (float *)pe->getBuffer(obj->cl_rgba_mem, 4*obj->getNumItems()*sizeof(float), 0);
	unsigned char * Uint8Buf = new unsigned char[4*obj->getNumItems()];
	for( int i=0; i<4*obj->getNumItems(); i++)
		Uint8Buf[i] = (unsigned char)(buf[i]);

	delete buf;
	return Uint8Buf;
}

void Generator::stepSim(int numSteps) {
	for( int i=0; i<numSteps; i++)
		pe->Step(*obj);
}

int Generator::Size(){
	return width*height;
}
