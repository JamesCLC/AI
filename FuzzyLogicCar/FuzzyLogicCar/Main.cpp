// MAT01 - Maths and AI
// Fuzzy Logic Driven Car
// by James Clayton
// Computer Games Technologoy Year 3 Semester 2 (2018)
// Student Number 1501082

// Includes
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Application.h"

void SFMLTest()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
		window.display();
	}
}


// Main Function
int main()
{
	Application myApp;

	myApp.Run();

	//SFMLTest();

	return 0;
}



