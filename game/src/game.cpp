#include "game.h"

Game::Game() : view(glm::vec4(0.0f, 0.0f, 20.0f, 0.0f)) {
	w.addObject(&view, view.position);
	glEnable(GL_DEPTH_TEST);
	std::vector<std::string> fileNames;

for( int j=0; j<10; j++ ) {
	fileNames.clear();
	for( int i=0; i<1000; i++ )
		fileNames.push_back("res/nonTriangle/untitled.obj");
//		fileNames.push_back("res/nonTriangle/untitled1.obj");

	gfxObjs = gle.glm.Load(fileNames);

	for( int i=0; i<gfxObjs.size(); i++ ) {
		glm::vec4 pos((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX );
		pos *= 500.0f;
		pos -= 250.0f;
		glm::quat q((float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5 );
		q = glm::normalize(q);
		Renderable * ro = new Renderable(pos, gfxObjs[i], q);
		w.addObject(ro,pos);
		w.renObjs.push_back(ro);
	}
}

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
//	std::cout << w.ot.UR[0] << std::endl;
	interface.Loop(&view);

	w.Wiggle();
	w.update();
	
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glm::vec4 * vpos = (glm::vec4 *)&(w.cloud->points[0]);
//	printv(vpos);
//	printv(view.position);
	for( int i=0; i<w.renObjs.size(); i++ ) {
		glm::vec4 * opos = (glm::vec4 *)&(w.cloud->points[w.renObjs[i]->index]);
		//gle.Render(&ren, w.renObjs[i], &view);
		gle.Render(&ren, w.renObjs[i], *opos, &view, view.position);
		//gle.Render(&ren, w.renObjs[i], w.renObjs[i]->position, &view, view->position);
	}
}




