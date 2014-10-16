#include "sprite.h"

Sprite::Sprite(SDL_Texture * tex, int numFrames, CLEngine * cle): clLoaded(0) {
	texture = tex;
	SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
	visRect.x = 0;
	visRect.y = 0;
	visRect.w = tw/numFrames;
	visRect.h = th;	

	if( cle != NULL ) {
		TextureProperty tp = getTexId(texture);
		int err;
		clObj = clCreateFromGLTexture2D(cle->getContext(), CL_MEM_READ_WRITE, tp.ttype, 0, tp.tid, &clLoaded);
		if( clLoaded < 0 ) { fprintf(stderr, "%i\n", clLoaded); perror("Could not create texture buffer."); exit(1); }
	} else {
		clObj = 0;
	}
}

Sprite::~Sprite() {
	if( !clLoaded )
		clReleaseMemObject(clObj);
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
