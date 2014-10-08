#include "generatorengine.h"

class Generator {
		GeneratorEngine ge;
		int width,height;
	public:
		Generator(int, int, CLEngine * cle_in=NULL);
		~Generator();
		unsigned char * getBuffer();
		void stepSim(int);
		int Size();
};

