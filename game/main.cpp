#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "util/cleanup.h"
#include "util/sdlutil.h"
#include "util/curlutil.h"

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

	CurlUtil cu;

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

	Object player( "res/Char1.png", 4, ren, cle );
	Object bgd( cu.getMap(42.2814, -83.7483), 1, ren, cle);
//	Object bgd( "res/Background.png", 1, ren, cle );
	world.addObject(&player);
	world.addObject(&bgd);

	printf("player tid: %i\n", getTexId(player.curSprite()->getTexture()).tid );
	printf("%s\n", glGetString(GL_RENDERER));

	bool quit = false;
	SDL_Event event;

	while( !quit ) {

		while( SDL_PollEvent( &event ) != 0 ) {
			switch( event.type ) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
				case SDLK_UP:
					fprintf(stderr, "keydown.\n");
					player.Move(0,-1);
					break;
				case SDLK_DOWN:
					player.Move(0,1);
					break;
				case SDLK_LEFT:
					player.Move(-1,0);
					break;
				case SDLK_RIGHT:
					player.Move(1,0);
					break;
				}
				break;
			}
		}

		world.stepSim(1);
		SDL_RenderClear(ren);
		world.Show();
		player.Step();
		SDL_RenderPresent(ren);

//		player.Move(1,1);

		SDL_Delay( 100 );
	}


	delete cle;

	cleanup(ren,window);
	SDL_Quit();

	return 0;
}


