#include "packedtextures.h"

PackedTextures::PackedTextures(SDL_Renderer * ren, std::vector<SDL_Texture *> & texVec, std::vector<SDL_Rect> & srcRect) {
	int sum_height=0;
	int max_width = 0;
	SDL_Rect tRect;
	tRect.x = 0;
	for( int i=0; i<texVec.size(); i++) {
		tRect.w = srcRect[i].w;
		tRect.h = srcRect[i].h;

		if( max_width < tRect.w )
			max_width = tRect.w;
		tRect.y = sum_height;
		sum_height += tRect.h;
		placements.push_back(tRect);
	}

	packedTexture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, max_width, sum_height);
	SDL_SetTextureBlendMode(packedTexture, SDL_BLENDMODE_NONE);

	SDL_Texture * pTarget = SDL_GetRenderTarget(ren);
	printf("Pack prev-renderer: %i\n",pTarget);
	printf("Pack new-texture: %i\n",packedTexture);
	SDL_SetRenderTarget(ren, packedTexture);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
	SDL_RenderClear(ren);

	for( int i=0; i<texVec.size(); i++) {
		SDL_RenderCopy(ren, texVec[i], &srcRect[i], &placements[i]);
	}

	SDL_SetRenderTarget(ren, pTarget);
	SDL_SetTextureBlendMode(packedTexture, SDL_BLENDMODE_BLEND);
}
PackedTextures::~PackedTextures() {
	SDL_DestroyTexture(packedTexture);
}

SDL_Rect PackedTextures::getPlacement(int ind) {
	return placements[ind];
}

SDL_Texture * PackedTextures::getTexture() {
	return packedTexture;
}
