#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "util/cleanup.h"
#include "util/sdlutil.h"

#include "object/sprite.h"
#include "clengine/clengine.h"
#include "world/world.h"

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

int main( int argc, char* args[] ) {
	SDL_Window* window = NULL;
	SDL_Surface * screenSurface = NULL;
	CLEngine * cle = new CLEngine();

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	window = SDL_CreateWindow( "Lesson 2", 100, 100, 640, 480, SDL_WINDOW_SHOWN );
	if( window == nullptr ) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if( ren == nullptr ) {
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}
	cle->Init();
	World world(640, 480, ren, cle);

	Object player( "res/Char1.png", 4, ren );
	Object bgd( "res/Background.png", 4, ren );
	world.addObject(&player);
	world.addObject(&bgd);

	for( int i=0; i<20; i++ ) {
		world.stepSim(1);
		SDL_RenderClear(ren);
		world.Show();
		spr.NextFrame();
		SDL_RenderPresent(ren);

		SDL_Delay( 200 );
	}


	delete cle;

	cleanup(ren,window);
	SDL_Quit();

	return 0;
}


