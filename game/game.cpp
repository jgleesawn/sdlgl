#include "game.h"

Game::Game() : view(glm::vec4(0.0f, 0.0f, 20.0f, 0.0f)) {
	glEnable(GL_DEPTH_TEST);
	std::vector<std::string> fileNames;
	for( int i=0; i<100; i++ )
		fileNames.push_back("res/nonTriangle/untitled1.obj");

	gfxObjs = gle.glm.Load(fileNames);

	for( int i=0; i<gfxObjs.size(); i++ ) {
		glm::vec4 pos((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX );
		pos *= 100.0f;
		pos -= 50.0f;
		glm::quat q((float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5 );
		q = glm::normalize(q);
		renObjs.push_back(new Renderable(pos, gfxObjs[i], q));
		sw.addVertex(renObjs.back());
	}
	sw.sort();

	interface.m[&Viewport::rotUp] = SDL_SCANCODE_UP;
	interface.m[&Viewport::rotDown] = SDL_SCANCODE_DOWN;
	interface.m[&Viewport::rotLeft] = SDL_SCANCODE_LEFT;
	interface.m[&Viewport::rotRight] = SDL_SCANCODE_RIGHT;
	interface.m[&Viewport::Forward] = SDL_SCANCODE_SPACE;
}

void Game::addInput(const void * state, int count, int stepsize) {
	interface.state = (Uint8 *)state;
	interface.count = count;

//	input in = {state, count, stepsize};
//	inputs.push_back(in);

}
void Game::Loop() {
	interface.Loop(&view);

	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	for( int i=0; i<renObjs.size(); i++ )
		gle.Render(&ren, renObjs[i], &view);
}




