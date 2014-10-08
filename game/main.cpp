#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "generator/generator.h"

#include <stdio.h>

class Obj{
	private:
		sf::Texture texture;
	public:
		sf::Sprite sprite;
		Obj();
		void FrameStep();
		void UpdateTexture(unsigned char *, int, int);
};


int main()
{

	sf::RenderWindow window(sf::VideoMode(600, 400), "2D Game");

	Generator gen(600, 400);
	gen.stepSim(1);

	Obj background;
	unsigned char * buf = gen.getBuffer();
	background.UpdateTexture(buf,600,400);
	delete buf;

//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(0,255,0,1));

	Obj obj1;

	sf::Clock clk;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(background.sprite,sf::RenderStates(sf::BlendNone));	
		window.draw(shape,sf::RenderStates(sf::BlendNone));
		window.draw(obj1.sprite,sf::RenderStates(sf::BlendAlpha));
		window.display();


		if( clk.getElapsedTime() > sf::milliseconds(200) ) {
			obj1.FrameStep();

			gen.stepSim(1);

			unsigned char * buf = gen.getBuffer();
			//printf("%p\n",buf);
			background.UpdateTexture(buf,600,400);
			delete buf;

			clk.restart();
		}
	}
	return 0;
}

Obj::Obj() {
	if( !texture.loadFromFile("res/Char1.png") )
		return;
	//texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setScale(2.0, 2.0);
	sprite.setTextureRect(sf::IntRect(0,0,20,20));
	sprite.setPosition(sf::Vector2f(40,40));
}

void Obj::FrameStep() {
	sf::IntRect rect = sprite.getTextureRect();
	if( rect.left+rect.width*2 < texture.getSize().x ) {
		rect.left += 20;
	} else {
		rect.left = 0;
	}
	sprite.setTextureRect(rect);
}

void Obj::UpdateTexture(unsigned char * buf, int width, int height) {
	texture.create(width, height);
	texture.update(buf,width,height,0,0);
	sprite.setTexture(texture, true);
	sprite.setScale(1.0, 1.0);
	sprite.setPosition(sf::Vector2f(0,0));
}


