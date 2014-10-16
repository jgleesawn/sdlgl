#include "object.h"

Object::Object() : curState(0) {
	movMod=1;
	SetPosition(0,0);
}

Object::Object(std::string sprFile, int numFrames, SDL_Renderer * ren, CLEngine * cle) : curState(0) {
	movMod=1;
	SetPosition(0,0);
	SDL_Texture * tex = loadTexture(sprFile, ren);
	sprites.push_back(new Sprite(tex, numFrames, cle) );
}

void Object::addSprite(Sprite * spr) {
	sprites.push_back(spr);
}

Sprite * Object::curSprite() {
	return sprites[curState];
}

void Object::Move(float x_mov, float y_mov) {
	x_mov *= movMod;
	y_mov *= movMod;
	pos.data[0] += x_mov;
	pos.data[1] += y_mov;
}
void Object::SetPosition(float x_pos, float y_pos) {
	pos.data[0] = x_pos;
	pos.data[1] = y_pos;
}

void Object::Step() {
	curSprite()->NextFrame();
}

void Object::DrawOn(SDL_Renderer * ren) {
	curSprite()->DrawOn(ren, pos.data[0], pos.data[1]);
}
