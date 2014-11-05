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

int main( int argc, char* args[] ) {
	SDL_Window* window = NULL;

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

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
//	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	GLEngine gle; //calls glewInit;
//	glEnable(GL_DEPTH_CLAMP);
 	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_CULL_FACE);
	BasicRenderer ren;
	Viewport view(glm::vec4(0,0,20,0));


	std::vector<std::string> fileNames;
	fileNames.push_back("res/nonTriangle/plane.obj");
	for( int i=0; i<100; i++ )
		fileNames.push_back("res/nonTriangle/untitled1.obj");
//	fileNames.push_back("res/nonTriangle/untitled.obj");

	std::vector<gfxObj_t> gfxObjs = gle.glm.Load(fileNames);
	SparseWorld sw;

	std::vector<Renderable *> renObjs;

	bool quit = false;
	SDL_Event event;

	renObjs.push_back(new Renderable(glm::vec4(0.0f, -50.0f, 0.0f, 0.0f), gfxObjs[0]));
	sw.addVertex(renObjs.back());
	for( int i=1; i<gfxObjs.size(); i++ ) {
		glm::vec4 pos((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, 0);
/*		glm::vec4 pos(0);
		pos[i/2] = (i%2)*2 - 1; */
		pos *= 100.0f;
		pos -= 50.0f;
		renObjs.push_back(new Renderable(pos, gfxObjs[i]));
		sw.addVertex(renObjs.back());
	}
	sw.sort();
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
					view.rotPerpendicular(-.1);
//					view.pos.z -= 1;
					break;
				case SDLK_DOWN:
					view.rotPerpendicular(.1);
//					view.pos.z += 1;
					break;
				case SDLK_LEFT:
					view.rotParallel(-.1);
//					view.pos.x -= 1;
					break;
				case SDLK_RIGHT:
					view.rotParallel(.1);
//					view.pos.x += 1;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_SPACE:
					view.Move(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
					break;
				}
				break;
			}
		}

		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		for( int i=0; i<renObjs.size(); i++ )
			gle.Render(&ren, renObjs[i], &view);

		SDL_GL_SwapWindow(window);

		SDL_Delay( 20 );
	}


	cleanup(&glcontext,window);
//	cleanup(ren,window);
	SDL_Quit();

	return 0;
}


