// Application.h
#pragma once

// Includes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::to_string;

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
	bool LoadFont();

private:
	int windowWidth = 1280;
	int windowHeight = 720;

	float maxVelocity = 0.6;
	float velocityIncrement = 0.01;

	sf::Vector2f velocity;
	sf::Vector2f displacement;

	sf::Texture car_texture;
	sf::Sprite car_sprite;

	sf::Shape* racingLine;

	// Text Output
	sf::Font font;
	sf::Text velocityText;
	sf::Text displacementText;
};

