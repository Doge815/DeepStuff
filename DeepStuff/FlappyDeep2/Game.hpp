#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include<functional>

#include "Container.hpp"
#include "Pipe.hpp"
#include "Constants.hpp"
#include "Bird.hpp"

#include "../NeuralNetwork/EvolutionNetwork/EvolutionCollection.hpp"
#include "../NeuralNetwork/EvolutionNetwork/EvolutionNetwork.hpp"

using namespace std;

class Game
{
	private:
		EvolutionCollection Collection;

		vector<Pipe*> Pipes;
		vector<Pipe*> DeadPipes;
		Pipe* ActivePipe;
		vector<Bird*> Birds;
		vector<Bird*> Deadbirds;

		int PipeSpawnDuration;
		int PipeSpawnTicker;

		void SpawnPipe();
	public:
		
		Game();
		void Render();
		void Update();
		void ReStart();
		
};

Game::Game()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(SizeX, SizeY), "FlappyDeep2", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(FPS);

	std::vector<LayerShape> size = { LayerShape((Activation*)(new ReLU()), 3, 1),
									 LayerShape((Activation*)(new ReLU()), 5, 1),
									 LayerShape((Activation*)(new ReLU()), 5, 1),
									 LayerShape((Activation*)(new Sigmoid()), 1, 1) };
	Collection = EvolutionCollection(100, NetworkShape(size), EvolutionProperties(0.2, 1.3));

	Container::RenderWindow = window;
	Container::WindowHeight = window->getSize().y;
	Container::WindowWidth = window->getSize().x;

	Pipe::gap = Container::WindowHeight / 5;
	Pipe::height = Container::WindowHeight;
	Pipe::widht = Container::WindowWidth / 20;
	Pipe::speed = Container::WindowWidth / 100;

	Bird::x = Container::WindowWidth / 10;
	Bird::height = Container::WindowHeight / 10;
	Bird::widht = Container ::WindowWidth / 15;

	ReStart();
	while (true)
	{
		Update();
		Render();
	}
}

void Game::Render()
{
	Container::RenderWindow->clear(sf::Color::Black);
	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Render();
	}

	for (size_t i = 0; i < DeadPipes.size(); i++)
	{
		DeadPipes[i]->Render();
	}

	for (size_t i = 0; i < Birds.size(); i++)
	{
		Birds[i]->Render();
	}
	Container::RenderWindow->display();
}

void Game::Update()
{
	if(Birds.size() == 0)
	{
		Collection.Evolve();
		ReStart();
		return;
	}
	/*
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Birds[0]->Jump();
	}
	*/
	PipeSpawnTicker++;
	if (PipeSpawnTicker == PipeSpawnDuration)
	{
		PipeSpawnTicker = 0;
		Game::SpawnPipe();
	}

	if (!DeadPipes.empty())
	{
		Pipe* LeftOne = DeadPipes[0];
		if (LeftOne->GetX() + Pipe::widht < 0)
		{
			DeadPipes.erase(DeadPipes.begin());
			delete LeftOne;
		}
	}

	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Update();
	}

	for (size_t i = 0; i < DeadPipes.size(); i++)
	{
		DeadPipes[i]->Update();
	}

	if (!Pipes.empty())
	{
		if(ActivePipe == NULL)
		{
			ActivePipe = Pipes[0];
			ActivePipe->Checked();
			Container::Score++;
		}
		if (ActivePipe->GetX() + Pipe::widht < Bird::x)
		{
			Pipes.erase(Pipes.begin());
			DeadPipes.push_back(ActivePipe);
			ActivePipe->Die();
			ActivePipe = NULL;
		}
	}

	if(ActivePipe != NULL)
	{
		if(Bird::widht + Bird::x > ActivePipe->GetX())
		{
			for (size_t i = 0; i < Birds.size(); i++)
			{
				Birds[i]->CollisionCheck(ActivePipe);
			}
		}
	}
;

	for (size_t i = 0; i < Birds.size(); i++)
	{
		if (Birds[i]->IsDead())
		{
			Bird* b = Birds[i];
			Birds.erase(Birds.begin() + i);
			Deadbirds.push_back(b);
		}
		else
		{
			double a = ActivePipe->GetX() + Pipe::widht - Bird::x - Bird::widht;
			double b = Pipe::speed;
			
			Birds[i]->Update(a, b);
		}
	}
	
	
}

void Game::SpawnPipe()
{
	Pipe* newPipe = new Pipe(Container::WindowWidth, 0);
	Pipes.push_back(newPipe);
}

void Game::ReStart()
{
	for (size_t i = 0; i < Pipes.size(); i++)
	{
		delete Pipes[i];
	}

	for (size_t i = 0; i < DeadPipes.size(); i++)
	{
		delete DeadPipes[i];
	}

	for (size_t i = 0; i < Deadbirds.size(); i++)
	{
		delete Deadbirds[i];
	}

	Container::Score = 0;

	Pipes = vector<Pipe*>();
	DeadPipes = vector<Pipe*>();
	ActivePipe = NULL;
	Birds = vector<Bird*>();
	Deadbirds = vector<Bird*>();

	PipeSpawnTicker =   0.7f * FPS - 1;
	PipeSpawnDuration = 0.7f * FPS;

	vector<Network*> n = Collection.GetNetworks();

	for (int i = 0; i < n.size(); i++)
	{
		EvolutionNetwork* e = dynamic_cast<EvolutionNetwork*>(n[i]);
		Bird* bird = new Bird(e);
		Birds.push_back(bird);
	}
}


