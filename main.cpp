#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

class Object{
	private:
		sf::Texture texture;
	public:
		sf::Sprite sprite;
		Object();
		void FrameStep();
};


int main()
{

	sf::RenderWindow window(sf::VideoMode(600, 400), "2D Game");

//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(0,255,0,1));

	Object obj1;

	sf::Clock clk;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(shape,sf::RenderStates(sf::BlendNone));
		window.draw(obj1.sprite,sf::RenderStates(sf::BlendAlpha));
		window.display();

		if( clk.getElapsedTime() > sf::milliseconds(200) ) {
			obj1.FrameStep();
			clk.restart();
		}
	}
	return 0;
}

Object::Object() {
	if( !texture.loadFromFile("res/Char1.png") )
		return;
	//texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setScale(2.0, 2.0);
	sprite.setTextureRect(sf::IntRect(0,0,20,20));
	sprite.setPosition(sf::Vector2f(40,40));
}

void Object::FrameStep() {
	sf::IntRect rect = sprite.getTextureRect();
	if( rect.left+rect.width*2 < texture.getSize().x ) {
		rect.left += 20;
	} else {
		rect.left = 0;
	}
	sprite.setTextureRect(rect);
}




