// Application.cpp

#include "Application.h"


Application::Application()
{
	// Load the textures.
	if (!LoadTextures())
	{
		std::cout << "ERROR! Textures were not loaded successfully!" << std::endl;
	}

	// Create the car.
	if (!CreateCar())
	{
		std::cout << "ERROR! Sprites were not created successfully!" << std::endl;
	}

	// Load the font.
	if (!LoadFont())
	{
		std::cout << "ERROR! Font was not loaded successfully!" << std::endl;
	}

	// Initialise vectors.
	velocity.x = 0;
	velocity.y = 0;

	displacement.x = 0;
	displacement.y = 0;

	// Set the car to it's default start position.
	car_sprite.setPosition(windowWidth/2, (windowHeight - 100.0f));

	// Seet up the Fuzzy Inference System
	m_FIS = new FuzzyLogic();
	m_FIS->Init();
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

	// Set the origin of the sprite to be it's centre point.
	float originX = car_sprite.getOrigin().x + (car_sprite.getLocalBounds().width / 2);
	float originY = car_sprite.getOrigin().y + (car_sprite.getLocalBounds().height / 2);

	car_sprite.setOrigin(originX, originY);

	// Scale the car sprite down.
	car_sprite.scale(0.20, 0.20);

	// Set the car to it's starting position.
	car_sprite.setPosition(windowWidth/2 + displacement.x, windowHeight/2);

	return true;
}


bool Application::LoadFont()
{
	// Load Domotika from file.
	if (!font.loadFromFile("Fonts/moon_get/moon_get-Heavy.ttf"))
	{
		return false;
	}

	// Set up the text object for displaying the car's velocity.
	velocityText.setFont(font);

	// Set the string to display.
	velocityText.setString("Velocity Default");

	// Set the character size.
	velocityText.setCharacterSize(24); // in pixels, not points!

	 // Set the color.
	velocityText.setFillColor(sf::Color::Red);

	// Set up the text object for displaying the car's displacement.
	displacementText.setFont(font);

	// Set the character size.
	displacementText.setCharacterSize(24); // in pixels, not points!

	// Set the color.
	displacementText.setFillColor(sf::Color::Red);

	displacementText.setPosition(0.0f, 25.0f);

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
			cin >> displacement.x;
			cout << endl;

			// Starting Velocity
			cout << "Initial velocity (Between 1 and -1.) = ";
			cin >> velocity.x;
			cout << endl;

			// User Confirmation
			cout << "Are " << displacement.x << " and " << velocity.x << " ok? (y/n)" << endl;
			cin >> userInput;

			if (!userInput.compare("Y") || !userInput.compare("y"))
			{
				// TO DO - RUN THORUGH FSM, DISPLAY OUTPUT.
				cout << (m_FIS->Update(velocity.x, displacement.x));

				inputConfirmed = true;
			} else
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
	// Move the Racing Line to the right.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
			racingLine->setPosition(racingLine->getPosition().x + 1, 0);
	}

	// Move the Racing Line to the left.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
			racingLine->setPosition(racingLine->getPosition().x - 1, 0);
	}

	if (racingLine->getPosition().x < 0)
	{
		racingLine->setPosition(0.0f, 0.0f);
	}
	else if (racingLine->getPosition().x > windowWidth)
	{
		racingLine->setPosition(windowWidth, 0.0f);
	}

	return true;
}


void Application::UpdateCar()
{
	// Update the car's displacement (used by FuzzyLogic)
	displacement.x = car_sprite.getPosition().x - racingLine->getPosition().x;

	//cout << velocity.x;

	// Pass the car's variables to the FIS.
	velocity.x = (m_FIS->Update(velocity.x, displacement.x));

	// Update the car's position.
	car_sprite.move(-velocity.x, 0.0f);
}


bool Application::Run()
{
	// Display the startup window.
	DisplayStartup();

	// Set up the Render Window
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Fuzzy Car by James Clayton");

	// Set up the Racing Line
	racingLine = new sf::RectangleShape(sf::Vector2f(1, windowHeight));
	racingLine->setPosition(windowWidth / 2, 0);
	racingLine->setFillColor(sf::Color::White);

	// Main Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Handle User Input.
		HandleInput();

		// Update the Car.
		UpdateCar();

		// Update the display strings.
		velocityText.setString(to_string(velocity.x));
		displacementText.setString(to_string(displacement.x));

		// Display the game.
		window.clear();
		window.draw(velocityText);
		window.draw(displacementText);
		window.draw((*racingLine));
		window.draw(car_sprite);
		window.display();
	}

	return false;
}
