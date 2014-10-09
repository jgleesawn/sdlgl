#include "world.h"

World::World(int w, int h, CLEngine * cle_in)i : we(cle_in) {
	rt.create(w,h);
	we.Init(rt.getTexture());
	width = w;
	height = h;
}

World::~World () { }

unsigned char * World::getBuffer() {
	float * buf;
	buf = (float *)we.getBuffer(0, 2, 4*Size()*sizeof(float), 0);
	unsigned char * Uint8Buf = new unsigned char[4*Size()];
	for( int i=0; i<4*Size(); i++)
		Uint8Buf[i] = (unsigned char)(buf[i]);
	delete buf;
	return Uint8Buf;
}

void World::stepSim(int numSteps) {
	for( int i=0; i<numSteps; i++)
		we.Step(NULL);
}

int World::Size(){
	return width*height;
}
