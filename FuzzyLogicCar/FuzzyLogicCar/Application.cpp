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
	//SFMLTest();
	CheckerboardTest();

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

	// Create the racing line's texture.
	if (!racingLine_texture.create(720, 100))
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

void Application::CheckerboardTest()
{
	// Code taken from [http://www.gamefromscratch.com/post/2015/10/20/SFML-CPP-Tutorial-Sprites-and-Textures.aspx] Accessed 18/02/2018

	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");
	sf::Event event;
	sf::Image image;
	image.create(640, 480, sf::Color::Black);

	bool isBlackPixel = false;
	sf::Color blackPixel(0, 0, 0, 255);
	sf::Color whitePixel(255, 255, 255, 255);

	//Loop through each vertical row of the image
	for (int y = 0; y < 480; y++)
	{
		//then horizontal, setting pixels to black or white in blocks of 8
		for (int x = 0; x < 640; x++)
		{
			if (isBlackPixel)
			{

				image.setPixel(x, y, blackPixel);
			}
			else
			{

				image.setPixel(x, y, whitePixel);
			}

			// Every 8th flip colour
			if (!(x % 8))
			{

				isBlackPixel = !isBlackPixel;
			}
		}

		// Offset again on vertical lines to create a checkerboard effect
		if (!(y % 8))
			isBlackPixel = !isBlackPixel;
	}

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);

	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				renderWindow.close();
			}
		}

		renderWindow.clear();
		renderWindow.draw(sprite);
		renderWindow.display();
	}
}

