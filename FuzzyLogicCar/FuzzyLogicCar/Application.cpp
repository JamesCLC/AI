// Application.cpp

#include "Application.h"


Application::Application()
{
	if (!LoadTextures())
	{
		std::cout << "ERROR! Textures were not loaded successfully!" << std::endl;
	}

	if (!CreateCar())
	{

		std::cout << "ERROR! Sprites were not created successfully!" << std::endl;
	}
}


Application::~Application()
{

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


bool Application::CreateCar()
{
	// Create the car.
	car_sprite.setTexture(car_texture);
	if (!car_sprite.getTexture())
	{
		// Error.
		return false;
	}

	// Set the origin of the sprite to be it's centre point
	float originX;
	float originY;

	originX = car_sprite.getOrigin().x + (car_sprite.getLocalBounds().width / 2);
	originY = car_sprite.getOrigin().y + (car_sprite.getLocalBounds().height / 2);

	car_sprite.setOrigin(originX, originY);

	// Scale the car sprite down
	car_sprite.scale(0.20, 0.20);

	// Set the car to it's starting position
	car_sprite.setPosition(windowWidth/2 , windowHeight/2);

	return true;
}


bool Application::DisplayStartup()
{
	string userInput;
	bool inputConfirmed = false;

	cout << "Welcome." << endl;
	cout << "This application simulates a 2D car being operated by a Fuzzy Inference System." << endl;
	cout << "Created by James Clayton, Student Number 1501082 at Abertay University, 2018." << endl;
	cout << endl;
	cout << "This application was built using SFML 2.4.1 {https://www.sfml-dev.org/]" << endl;
	cout << "and FuzzyLite 6.0 C++ Edition [https://www.fuzzylite.com/]." << endl;
	cout << endl;
	cout << "Would you like to set initial conditions for the application? (y/n)" << endl;

	cin >> userInput;

	if (!userInput.compare("Y") || !userInput.compare("y"))
	{
		while (!inputConfirmed)
		{
			cout << endl << "Please enter your desired conditions." << endl << endl;;
			cout << "Please note: Negative value correspond to the left of the racing line," << endl;
			cout << "positive values correspond to the right of the racing line." << endl << endl;

			// Starting Displacement
			cout << "Initial distance from Racing Line (Between " << windowWidth / 2 << " and " << -1 * windowWidth / 2 << ".) = ";
			cin >> startingDisplacement;
			cout << endl;

			// Starting Velocity
			cout << "Initial velocity (Between x and y.) = ";
			cin >> startingVelocity;
			cout << endl;

			// User Confirmation
			cout << "Are " << startingDisplacement << " and " << startingVelocity << " ok? (y/n)" << endl;
			cin >> userInput;

			if (!userInput.compare("Y") || !userInput.compare("y"))
			{
				inputConfirmed = true;
			}

			else
			{
				inputConfirmed = false;
			}

		} // end while

	} // end if

	else if (!userInput.compare("N") || !userInput.compare("n"))
	{
		cout << "Default starting values will be used." << endl;
	}

	return false;
}


bool Application::HandleInput()
{
	// Accelerate to the right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (velocity.x <= maxVelocity)
		{
			velocity.x += velocityIncrement;
		}
	}

	// Move Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (velocity.x >= (maxVelocity * -1))
		{
			velocity.x -= velocityIncrement;
		}
	}

	return true;
}


void Application::UpdateCar()
{
	// Update the displacement variable.
	displacement.x += velocity.x;

	// Reflect these changes in the car's location.
	car_sprite.setPosition(displacement);

}


bool Application::Run()
{
	// Display the startup window.
	DisplayStartup();

	// Set up the Render Window
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Fuzzy Car by James Clayton");

	// Set up the Racing Line
	sf::RectangleShape racingLine(sf::Vector2f(1, windowHeight));
	racingLine.setPosition(windowWidth / 2, 0);
	racingLine.setFillColor(sf::Color::White);

	// Set the starting values for the car's movement
	velocity.x = startingVelocity;
	displacement.x = startingDisplacement;

	// Main Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		HandleInput();

		UpdateCar();

		window.clear();
		window.draw(racingLine);
		window.draw(car_sprite);
		window.display();

		
	}

	return false;
}

/*
	Hello, James! Here's a quick rundown on what needs to be done.
	
	I need to rethink the "Displacement" thing. At the moment, is just a float, and has no real basis on the racing line.
	I'll need to get this working to the point where the car's velocity is measured from the racing line and not just 3D space.
	Once that's done, I can have another look at the MATLAB stuff, finish my first design, ask Dr. King about it and then move on
	to implementing the AI.

	Good luck, you beautiful bastard! You can do this!
*/
