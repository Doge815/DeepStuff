#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Container
{
	public:
		static sf::RenderWindow* RenderWindow;
		static int WindowHeight;
		static int WindowWidth;
		static int Score;
};

sf::RenderWindow *Container::RenderWindow;
int Container::WindowHeight;
int Container::WindowWidth;
int Container::Score;