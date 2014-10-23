#include "world.h"

World::World(int w, int h, SDL_Renderer * ren, CLEngine * cle_in) : we(cle_in), focus(0) {
	renderer = ren;
	rendtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
//Possibly remove Init and just use addTexture
	we.Init(rendtex);

	width = w;
	height = h;
}

World::~World () { 
	SDL_DestroyTexture(rendtex);
}

//Currently requires textures to be packed.
void World::addObject( Object * obj ) {
	objs.push_back(obj);
//Only Adds Current Texture, expand to all animation textures.
	we.addTexture(obj->curSprite()->getTexture());
}

//Object order currently hard-coded into the stepSim
void World::stepSim(int numSteps) {
	//Stop-gap
	SDL_Texture * pTarget = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, rendtex);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	objs[0]->DrawOn(renderer);

	SDL_RenderPresent(renderer);
	glFinish();
	SDL_SetRenderTarget(renderer,pTarget); 
	
	wePasser wp;
	wp.rendtex = rendtex;
	wp.obj = objs[focus];
	for( int i=0; i<numSteps; i++)
		we.Step(&wp);
	objs[focus]->movMod = wp.movMod;
	fprintf(stderr, "movMod: %f\n", wp.movMod);
}

int World::Size(){
	return width*height;
}

void World::Show() {
//	SDL_RenderCopy(renderer, rendtex, NULL, NULL);
//	objs[0]->DrawOn(renderer);
//	This code draws from array. Using stop-gap just to test.
	for( int i=0; i<objs.size(); i++) {
		objs[i]->DrawOn(renderer);
	}
}
