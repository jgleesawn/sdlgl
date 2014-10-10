#include <SFML/Graphics.hpp>

#include "generator/generator.h"
#include "world/world.h"

#include <stdio.h>

int main()
{

	CLEngine cle;
	sf::RenderWindow window(sf::VideoMode(600, 400), "2D Game");
	cle.Init();

	Generator gen(600, 400, &cle);
	gen.stepSim(5000);

	Object background;
	sf::Texture tex;
	tex.create(600,400);
	tex.update(gen.getBuffer());
	background.addAnimation(new Animation(tex));

	World world(600, 400, &cle);
	Object Player("res/Char1.png", 4);
	world.addObject( &Player );
	world.addObject( &background );


//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(0,255,0,1));

	sf::Clock clk;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) 
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					Player.Move(0,-1);
					break;
				case sf::Keyboard::Down:
					Player.Move(0,1);
					break;
				case sf::Keyboard::Left:
					Player.Move(-1,0);
					break;
				case sf::Keyboard::Right:
					Player.Move(1,0);
					break;
				}
				break;
			}
		}

		window.clear();
		world.Show( &window );
//		window.draw(background.sprite,sf::RenderStates(sf::BlendNone));	
//		window.draw(shape,sf::RenderStates(sf::BlendNone));
//		window.draw(obj1.sprite,sf::RenderStates(sf::BlendAlpha));
		window.display();


		if( clk.getElapsedTime() > sf::milliseconds(200) ) {
			Player.Step();

			clk.restart();
		}
	}
	return 0;
}


