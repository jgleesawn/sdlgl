#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "util/cleanup.h"
#include "util/sdlutil.h"
#include "util/curlutil.h"

#include "texturemanager/texturemanager.h"
#include "clengine/clengine.h"
#include "world/world.h"

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void test_packedTextures(SDL_Renderer * ren, CLEngine * cle) {
	Object player( "res/Char1.png", 4, ren, cle );
	TextureManager().getSingleton()->packTextures(ren);
	
	SDL_RenderClear(ren);
	player.DrawOn(ren);
	SDL_RenderPresent(ren);
	
	SDL_Delay(1000);
	
	Object bgd( cu.getMap(42.2814, -83.7483), 1, ren, cle);
	TextureManager().getSingleton()->packTextures(ren);
	
	SDL_RenderClear(ren);
	bgd.DrawOn(ren);
	player.DrawOn(ren);
	SDL_RenderPresent(ren);
	
	SDL_Delay(1000);
	
	Object third( cu.getMap(40, -80), 1, ren, cle);
	TextureManager().getSingleton()->packTextures(ren);
	
	SDL_RenderClear(ren);
	third.DrawOn(ren);
//	bgd.DrawOn(ren);
	player.DrawOn(ren);
	SDL_RenderPresent(ren);
	
	SDL_Delay(1000);
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

	test_packedTextures(ren, cle);

	AtlasLocation al = player.curSprite()->getAtlasLocation();
	printf("atlas: %i\nindex: %i\n", al.atlas, al.index);
	al = bgd.curSprite()->getAtlasLocation();
	printf("atlas: %i\nindex: %i\n", al.atlas, al.index);
	printf("main tid: %i\nttype: %i\n", getTexId(player.curSprite()->getTexture()).tid, getTexId(player.curSprite()->getTexture()).ttype);

//	Object bgd( "res/Background.png", 1, ren, cle );
	world.addObject(&bgd);
	world.addObject(&player);

	printf("player tid: %i\n", getTexId(player.curSprite()->getTexture()).tid );
	printf("%s\n", glGetString(GL_RENDERER));

	world.stepSim(1);
	SDL_RenderClear(ren);
	world.Show();
	SDL_RenderPresent(ren);

	player.Step();


	delete cle;
	delete TextureManager().getSingleton();

	cleanup(ren,window);
	SDL_Quit();

	return 0;
}


