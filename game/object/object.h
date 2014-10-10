#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "animation.h"

class Object {
		std::vector<Animation *> sprites;
		int curState;
	public:
		float movMod;	//Stop Gap

		Object();
		Object(const char *, int);
		void addAnimation(Animation *);
		Animation * curAnimation();
		void Move(float, float);
		void Step();
};


#endif
