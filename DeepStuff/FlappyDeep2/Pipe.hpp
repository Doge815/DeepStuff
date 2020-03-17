#pragma once
#include <SFML/Graphics.hpp>

#include "Container.hpp"

class Pipe
{
	private:
		int x;
		int y;
		sf::RectangleShape* rs;

	public:
		static int wight;
		static int height;
		static int speed;
		static int gap;

		void Render();
		void Update();
		void Die();
		void Checked();
		int GetX();
		int GetY();
		Pipe(int X, int Y);
		~Pipe();
};

void Pipe::Render()
{
	rs->setPosition(x, y + gap + Container::WindowHeight / 2);
	Container::RenderWindow->draw(*rs);
	rs->setPosition(x, y - gap + Container::WindowHeight / 2 - height);
	Container::RenderWindow->draw(*rs);
}

Pipe::Pipe(int X, int Y)
{
	x = X;
	y = Y;
	rs = new sf::RectangleShape();
	rs->setSize(Vector2f(wight, height));
	rs->setFillColor(Color::Green);
}

Pipe::~Pipe()
{
	delete rs;
}

void Pipe::Update()
{
	x -= speed;
}

int Pipe::GetX()
{
	return x;
}

int Pipe::GetY()
{
	return y;
}

void Pipe::Die()
{
	rs->setFillColor(Color::Yellow);
}

void Pipe::Checked()
{
	rs->setFillColor(Color::Blue);
}

int Pipe::wight;
int Pipe::height;
int Pipe::gap;
int Pipe::speed;