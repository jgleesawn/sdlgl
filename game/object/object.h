#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <vector>
#include <string>

#include "util/sdlutil.h"
#include "sprite.h"

class Object {
		std::vector<Sprite *> sprites;
		int curState;
		float x, y;
	public:
		float movMod;	//Stop Gap

		Object();
		Object(std::string, int, SDL_Renderer *);

		void addSprite(Sprite *);
		Sprite * curSprite();
		void Move(float, float);
		void Step();
		void DrawOn(SDL_Renderer *);
		void getX() { return x; }
		void getY() { return y; }
};


#endif
