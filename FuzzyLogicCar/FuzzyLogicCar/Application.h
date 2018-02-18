#pragma once

// Includes
#include <SFML/Graphics.hpp>
#include <iostream>

// Application Class
class Application
{
public:
	Application();
	~Application();

	bool Run();
	void SFMLTest();

private:
	bool CreateImages();
	bool LoadTextures();
	bool LoadSprites();

	sf::Texture car_texture;
	sf::Sprite car_sprite;

	sf::Image racingLine_image;
	sf::Texture racingLine_texture;
	sf::Sprite racingLine_sprite;
};

