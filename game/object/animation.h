#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation : public sf::Sprite {

		int numFrames;
		int curFrame;
		int wFrame,hFrame;
	public:
		Animation(sf::Texture tex, int frameNum=1);
		void Step();
		void Reset() {curFrame = 0;}
		int getFrame() {return curFrame;}
		int getWFrame() {return wFrame;}
		int getHFrame() {return hFrame;}
};



#endif
