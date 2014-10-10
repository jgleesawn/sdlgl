#include "world.h"

World::World(int w, int h, CLEngine * cle_in) : we(cle_in), focus(0) {
	rt.create(w,h);
	we.Init(rt.getTexture());

	width = w;
	height = h;
}

World::~World () { }

void World::addObject( Object * obj ) {
	objs.push_back(obj);
//Only Adds Current Texture, expand to all animation textures.
	we.addTexture(*obj->curAnimation()->getTexture());
}

unsigned char * World::getBuffer() {
//	float * buf;
//	buf = (float *)we.getBuffer(0, 2, 4*Size()*sizeof(float), 0);
	unsigned char * Uint8Buf = new unsigned char[4*Size()];
//	for( int i=0; i<4*Size(); i++)
//		Uint8Buf[i] = (unsigned char)(buf[i]);
//	delete buf;
	return Uint8Buf;
}

void World::stepSim(int numSteps) {
	//Stop-gap
	rt.clear();
	sf::CircleShape c1(100.f);
	c1.setFillColor(sf::Color(0,255,0,1));
	c1.setPosition(0,0);
	sf::CircleShape c2(100.f);
	c2.setFillColor(sf::Color(0,0,255,1));
	c2.setPosition(300,0);
	rt.draw(c1);
	rt.draw(c2);
	//rt.draw(* objs[1]->curAnimation());
	rt.display();
	
	wePasser wp;
	wp.rt = &rt;
	wp.anim = objs[focus]->curAnimation();
	for( int i=0; i<numSteps; i++)
		we.Step(&wp);
	objs[focus]->movMod = wp.movMod;
}

int World::Size(){
	return width*height;
}

void World::Show( sf::RenderTarget * target ) {
	sf::Sprite s(rt.getTexture());
//	target->draw(s);
	target->draw(*objs[0]->curAnimation());
/*	This code draws from array. Using stop-gap just to test.
	for( int i=0; i<objs.Size(); i++) {
		target->draw( *objs[i].curAnimation() );
	}
*/
}
