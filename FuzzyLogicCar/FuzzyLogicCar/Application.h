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
	bool LoadTextures();
	bool LoadSprites();

	sf::Texture car_texture;
	sf::Sprite car_sprite;
};

