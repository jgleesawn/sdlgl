#ifndef PACKEDTEXTURES_H
#define PACKEDTEXTURES_H

#include <SDL2/SDL.h>
#include <vector>

class PackedTextures {
	std::vector<SDL_Rect> placements;
	SDL_Texture * packedTexture;
public:
	PackedTextures(SDL_Renderer *, std::vector<SDL_Texture *> &, std::vector<SDL_Rect> &);
//	PackedTextures(SDL_Texture * t, SDL_Rect * r) {}
	~PackedTextures();

	SDL_Rect getPlacement(int);
	SDL_Texture * getTexture();
};

#endif
