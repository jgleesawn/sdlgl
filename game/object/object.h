#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <vector>
#include <string>

#include "clengine/clengine.h"
#include "util/sdlutil.h"
#include "sprite.h"

#include "util/othertypes.h"

class Object {
		std::vector<Sprite *> sprites;
		int curState;
		vec4<float> pos;
	public:
		float movMod;	//Stop Gap

		Object();
		Object(std::string, int, SDL_Renderer *, CLEngine * cle = NULL);

		void addSprite(Sprite *);
		Sprite * curSprite();
		void Move(float, float);
		void SetPosition(float, float);
		void Step();
		void DrawOn(SDL_Renderer *);
		float getX() { return pos.data[0]; }
		float getY() { return pos.data[1]; }
};


#endif
