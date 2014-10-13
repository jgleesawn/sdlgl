#include "sprite.h"

Sprite::Sprite(SDL_Texture * tex, int numFrames) {
	texture = tex;
	SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
	visRect.x = 0;
	visRect.y = 0;
	visRect.w = tw/numFrames;
	visRect.h = th;	
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
}

void Sprite::NextFrame() {
	visRect.x += visRect.w;
	if( visRect.x >= tw )
		visRect.x = 0;
}

void Sprite::DrawOn(SDL_Renderer * ren, int x, int y ) {
	SDL_Rect outRect;
	outRect.x = x;
	outRect.y = y;
	outRect.w = visRect.w;
	outRect.h = visRect.h;
	SDL_RenderCopy(ren, texture, &visRect, &outRect);
}
