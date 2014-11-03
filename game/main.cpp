#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
//#include <GL/glu.h>

#include <stdio.h>
#include <string>
#include <iostream>

#include <glm/glm.hpp>

#include "util/cleanup.h"
#include "util/sdlutil.h"

#include "glmanager/glengine.h"
#include "sparseworld/sparseworld.h"

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

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

//	window = SDL_CreateWindow( "SDL Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN );
	window = SDL_CreateWindow( "SDL Game", 100, 100, 640, 640, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	if( window == nullptr ) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	GLEngine gle;

	bool quit = false;
	SDL_Event event;

	SparseWorld sw;
//	sw.test();
	for( int i=0; i<1000; i++ ) {
		glm::vec4 pos((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, 0);
		sw.addVertex(new Object(pos));
		sw.sort();
	}
//	printf("\n\n");
//	sw.test();

	while( !quit ) {

		while( SDL_PollEvent( &event ) != 0 ) {
			switch( event.type ) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
				break;
			}
		}

//		SDL_RenderClear(ren);
//		SDL_RenderPresent(ren);

		SDL_Delay( 100 );
	}


	cleanup(&glcontext,window);
//	cleanup(ren,window);
	SDL_Quit();

	return 0;
}


