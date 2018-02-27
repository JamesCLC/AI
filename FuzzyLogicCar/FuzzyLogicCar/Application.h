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
	void UpdateCar();

private:
	bool LoadTextures();
	bool CreateCar();

private:
	int windowWidth = 1280;
	int windowHeight = 720;

	int startingVelocity = 0;
	int startingDisplacement = 0;

	// Limiting Values?
	float maxVelocity = 0.3;
	float velocityIncrement = 0.01;

	sf::Vector2f velocity;
	sf::Vector2f displacement;

	sf::Texture car_texture;
	sf::Sprite car_sprite;
};

