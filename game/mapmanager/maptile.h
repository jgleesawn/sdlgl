#ifndef MAPTILE_H
#define MAPTILE_H

#include "util/curlutil.h"

class MapTile {
	SDL_Texture * visual;
	SDL_Texture * Collisions;
	vec4<float> pos;
public:
	MapTile(vec4<float>);
	~MapTile();
	vec4<float> Right();
	vec4<float> Left();
	vec4<float> Up();
	vec4<float> Down();
};

#endif
