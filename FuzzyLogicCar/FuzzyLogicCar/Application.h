// Application.h

#pragma once

// Includes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

using std::string;

// Application Class
class Application
{
public:
	Application();
	~Application();

	bool Run();
	bool DisplayStartup();
	bool HandleInput();

private:
	bool LoadTextures();
	bool LoadSprites();

	int windowWidth = 1280;
	int windowHeight = 720;

	int startingDisplacement = 200;
	int startingVelocity = 5;

	sf::Texture car_texture;
	sf::Sprite car_sprite;
};

