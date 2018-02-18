#include "Application.h"



Application::Application()
{
	if (!CreateImages())
	{
		std::cout << "ERROR! Image was not created successfully!" << std::endl;
	}

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

bool Application::CreateImages()
{
	// Code based on [http://www.gamefromscratch.com/post/2015/10/20/SFML-CPP-Tutorial-Sprites-and-Textures.aspx]

	racingLine_image.create(0, 720, sf::Color::White);

	// TO DO -  Add error handling?

	return true;
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

	// Create the racing line's texture.
	if (!racingLine_texture.loadFromImage(racingLine_image))
	{
		// Error.
		texturesLoaded = false;
	}

	return texturesLoaded;
}

bool Application::LoadSprites()
{
	// Create the car.
	car_sprite.setTexture(car_texture);
	if (!car_sprite.getTexture())
	{
		// Error.
		return false;
	}

	// Create the Racing Line.
	racingLine_sprite.setTexture(racingLine_texture);
	if (!racingLine_sprite.getTexture())
	{
		// Error.
		return false;
	}

	return true;
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
		window.draw(shape);
		window.draw(car_sprite);
		window.draw(racingLine_sprite);
		window.display();
	}
}


