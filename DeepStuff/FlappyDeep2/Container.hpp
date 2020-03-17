#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Container
{
	public:
		static sf::RenderWindow* RenderWindow;
		static int WindowHeight;
		static int WindowWidth;
};

sf::RenderWindow *Container::RenderWindow;
int Container::WindowHeight;
int Container::WindowWidth;