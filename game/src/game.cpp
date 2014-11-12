#include "game.h"

Game::Game() {
	glewInit();
	ren = new BasicRenderer();
	ren->setGLM(&glm);

	view = new Viewport(glm::vec4(0.0f, 0.0f, 20.0f, 0.0f));
	w.camera = w.addObject(view, view->position);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	std::vector<std::string> fileNames;

for( int j=0; j<10; j++ ) {
	fileNames.clear();
	for( int i=0; i<1000; i++ )
		fileNames.push_back("res/nonTriangle/untitled.obj");
//		fileNames.push_back("res/nonTriangle/untitled1.obj");

	gfxObjs = glm.Load(fileNames);

	for( int i=0; i<gfxObjs.size(); i++ ) {
		glm::vec4 pos((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX );
		pos *= 500.0f;
		pos -= 250.0f;
		pos.w = 0.0f;
		glm::quat q((float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5 );
		q = glm::normalize(q);
		Renderable * ro = new Renderable(pos, gfxObjs[i], q);

		w.addObject(ro,pos);
		w.makeRenderable(ro->index);
	}
}

	interface.m[&World::MoveFocusForward] = SDL_SCANCODE_W;
	interface.m[&World::MoveFocusLeft] = SDL_SCANCODE_A;
	interface.m[&World::MoveFocusRight] = SDL_SCANCODE_D;
	interface.m[&World::MoveFocusBack] = SDL_SCANCODE_S;

	interface.m[&World::RotFocusRight] = SDL_SCANCODE_RIGHT;
	interface.m[&World::RotFocusLeft] = SDL_SCANCODE_LEFT;
	interface.m[&World::RotFocusUp] = SDL_SCANCODE_UP;
	interface.m[&World::RotFocusDown] = SDL_SCANCODE_DOWN;

	interface.m[&World::focusCamera] = SDL_SCANCODE_SPACE;
	interface.m[&World::focusNext] = SDL_SCANCODE_TAB;
}

Game::~Game() {
	if( ren )
		delete ren;
}

void Game::addInput(const void * state, int count, int stepsize) {
	interface.state = (Uint8 *)state;
	interface.count = count;

//	input in = {state, count, stepsize};
//	inputs.push_back(in);

}
void Game::Loop() {
//	std::cout << w.ot.UR[0] << std::endl;
	interface.Loop(&w);

	w.Wiggle();
	w.update();


	std::vector<float> k_sqr;
	w.selection.clear();
	w.octree.nearestKSearch(*w.cloud, w.camera, 15, w.selection, k_sqr);

	
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glm::vec4 * vpos = (glm::vec4 *)&(w.cloud->points[w.camera]);
	ren->Use();
	ren->setCameraRotationPerspective( view->getRotMat(), view->perspectiveMatrix );
	ren->setCameraPos(*vpos);
	for( int i=0; i<w.renObjs.size(); i++ ) {
		glm::vec4 * opos = (glm::vec4 *)&(w.cloud->points[w.renObjs[i]->index]);
		ren->Render(w.renObjs[i], *opos);
	}
	std::vector<int>::iterator it;
	for( it = w.selection.begin()+1; it != w.selection.end(); it++ ) {
		glm::vec4 * opos = (glm::vec4 *)&(w.cloud->points[*it]);
		ren->Wireframe((Renderable *)w.objects[*it], *opos);
	}
//FIX THIS, relying on camera being Object[0]
//	if( w.focus ) {
//		glm::vec4 * opos = (glm::vec4 *)&(w.cloud->points[w.objects[w.focus]->index]);
//		ren->Wireframe((Renderable *)w.objects[w.focus], *opos);
//	}
}




