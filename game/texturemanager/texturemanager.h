#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "packedtextures.h"
#include "util/sdlutil.h"

#include <vector>

struct TextureLocation {
	SDL_Texture * texture;
	SDL_Rect location;
};

struct AtlasLocation {
	int atlas;
	int index;
};

class TextureManager {

	static class TextureManager * mSingleton;

	std::vector<PackedTextures> textures;
	std::vector<SDL_Texture *> unpacked;
	std::vector<SDL_Rect> rects;

public:
	TextureManager();
	~TextureManager();

	TextureManager * getSingleton();

	TextureLocation getTexture(AtlasLocation);
	AtlasLocation addTexture(const std::string &, SDL_Renderer *);
	AtlasLocation addTexture(SDL_Texture *);
	AtlasLocation addTexture(SDL_Texture *, SDL_Rect);
	void packTextures(SDL_Renderer *);
};


#endif
