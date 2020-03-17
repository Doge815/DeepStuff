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
		
		Game(sf::RenderWindow* rw);
		void Render();
		void Update();
		void ReStart();
		
};

Game::Game(sf::RenderWindow* rw)
{
	std::vector<LayerShape> size = { LayerShape((Activation*)(new ReLU()), 4, 1),
									 LayerShape((Activation*)(new ReLU()), 5, 1),
									 LayerShape((Activation*)(new ReLU()), 5, 1),
									 LayerShape((Activation*)(new Sigmoid()), 1, 1) };
	Collection = EvolutionCollection(100, NetworkShape(size), EvolutionProperties(0.2, 1.3));

	Container::RenderWindow = rw;
	Container::WindowHeight = rw->getSize().y;
	Container::WindowWidth = rw->getSize().x;

	Pipe::gap = Container::WindowHeight / 5;
	Pipe::height = Container::WindowHeight;
	Pipe::wight = Container::WindowWidth / 20;
	Pipe::speed = Container::WindowWidth / 100;

	Bird::x = Container::WindowWidth / 10;
	Bird::height = Container::WindowHeight / 10;
	Bird::wight = Container ::WindowWidth / 15;

	ReStart();
}

void Game::Render()
{
	#if true
	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Render();
	}

	for (size_t i = 0; i < DeadPipes.size(); i++)
	{
		DeadPipes[i]->Render();
	}
	#endif

	for (size_t i = 0; i < Birds.size(); i++)
	{
		Birds[i]->Render();
	}
	
}

void Game::Update()
{
	if(Birds.size() == 0)
	{
		ReStart();
		return;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Birds[0]->Jump();
	}

	PipeSpawnTicker++;
	if (PipeSpawnTicker == PipeSpawnDuration)
	{
		PipeSpawnTicker = 0;
		Game::SpawnPipe();
	}

	if (!DeadPipes.empty())
	{
		Pipe* LeftOne = DeadPipes[0];
		if (LeftOne->GetX() + Pipe::wight < 0)
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
		}
		if (ActivePipe->GetX() + Pipe::wight < Bird::x)
		{
			Pipes.erase(Pipes.begin());
			DeadPipes.push_back(ActivePipe);
			ActivePipe->Die();
			ActivePipe = NULL;
		}
	}

	if(ActivePipe != NULL)
	{
		if(Bird::wight + Bird::x > ActivePipe->GetX())
		{
			for (size_t i = 0; i < Birds.size(); i++)
			{
				Birds[i]->CollisionCheck(ActivePipe);
			}
		}
	}

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
			Birds[i]->Update();
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

	Pipes = vector<Pipe*>();
	DeadPipes = vector<Pipe*>();
	ActivePipe = NULL;
	Birds = vector<Bird*>();
	Deadbirds = vector<Bird*>();

	PipeSpawnTicker =   0.7f * FPS - 1;
	PipeSpawnDuration = 0.7f * FPS;

	//NetworkCollection.Evolve();

	Bird* bird = new Bird();
	Birds.push_back(bird);
}


