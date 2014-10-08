#include "physicsengine.h"
#include "object.h"

class Generator {
		PhysicsEngine * pe;
		Object * obj;
		int width,height;
	public:
		Generator(int, int);
		~Generator();
		unsigned char * getBuffer();
		void stepSim(int);
		int Size();
};

