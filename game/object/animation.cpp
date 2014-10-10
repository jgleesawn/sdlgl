#include "animation.h"

Animation::Animation(sf::Texture tex, int frameNum) {
	numFrames = frameNum;
	curFrame = 0;
	wFrame = tex.getSize().x;
	wFrame /= frameNum;
	hFrame = tex.getSize().y;
	sf::IntRect rect(0, 0, wFrame, hFrame);
	setTexture(tex, true);
	setTextureRect(rect);
}

void Animation::Step() {
	curFrame++;
	if( curFrame > numFrames )
		curFrame = 0;
	sf::IntRect rect(curFrame*wFrame, 0, (curFrame+1)*wFrame, hFrame);
	setTextureRect(rect);
}
