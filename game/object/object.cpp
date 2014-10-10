#include "object.h"

Object::Object() : curState(0) {}

Object::Object(const char * sprFile, int numFrames) : curState(0) {
	sf::Texture * tex = new sf::Texture;
	if( !tex->loadFromFile(sprFile) ) {
		printf("Couldn't load texture %s",sprFile);
		exit(1);
	}
	sprites.push_back(new Animation(*tex, numFrames) );
}

void Object::addAnimation(Animation * anim) {
	sprites.push_back(anim);
}

Animation * Object::curAnimation() {
	return sprites[curState];
}

void Object::Move(float x, float y) {
//	x *= movMod;
//	y *= movMod;
	for( int i=0; i<sprites.size(); i++)
		sprites[i]->move(x,y);
}

void Object::Step() {
	curAnimation()->Step();
}
