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
		void SetPosition(float, float);
		void Step();
		void DrawOn(SDL_Renderer *);
		float getX() { return x; }
		float getY() { return y; }
};


#endif
