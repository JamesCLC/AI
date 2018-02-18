#include "Application.h"



Application::Application()
{
	if (!LoadTextures())
	{
		std::cout << "ERROR! Textures were not loaded successfully!" << std::endl;
	}

	if (!LoadSprites())
	{
		std::cout << "ERROR! Sprites were not created successfully!" << std::endl;
	}
}


Application::~Application()
{

}

bool Application::Run()
{
	SFMLTest();

	return false;
}

bool Application::LoadTextures()
{
	bool texturesLoaded = true;
	
	// Load in the car's texture.
	if (!car_texture.loadFromFile("Images/car.png"))
	{
		// Error.
		texturesLoaded = false;
	}

	return texturesLoaded;
}

bool Application::LoadSprites()
{
	bool spritesLoaded = true;

	// Create the car.
	car_sprite.setTexture(car_texture);
	if (!car_sprite.getTexture())
	{
		// Error.
		spritesLoaded = false;
	}

	return spritesLoaded;
}

void Application::SFMLTest()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		window.draw(car_sprite);
		window.display();
	}
}