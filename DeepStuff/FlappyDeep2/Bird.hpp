#pragma once
#include <SFML/Graphics.hpp>

#include "../NeuralNetwork/EvolutionNetwork/EvolutionNetwork.hpp"

#include "Container.hpp"
#include "Pipe.hpp"

#include <iostream>

class Bird
{
    private:
        int y;
        int Jumpheight;
        bool dead;
        sf::RectangleShape* rs;
        EvolutionNetwork* network;
    public:
        static int widht;
		static int height;
        static int x;

        static const int gravity = 2;
        static const int jumpPower = 25;

        Bird(EvolutionNetwork* n);
        ~Bird();
        void Jump();
        void Update();
        void Update(double a, double b);
        void Render();
        void CollisionCheck(Pipe* pipe);
        bool IsDead();
};

void Bird::Render()
{
    rs->setPosition((float)x, (float)y + Container::WindowHeight / 2);
    Container::RenderWindow->draw(*rs);
}

Bird::Bird(EvolutionNetwork* n)
{
    network = n;
    dead = false;
    y = 0 - height / 2;
    Jumpheight = 0;
    rs = new RectangleShape();
    rs->setSize(Vector2f((float)widht, (float)height));
    rs->setFillColor(Color::Red);
} 

Bird::~Bird()
{
    //Todo: Cleanup
}

void Bird::Jump()
{
    if(Jumpheight < jumpPower * 4 / 5)
    Jumpheight = jumpPower;
}

void Bird::CollisionCheck(Pipe* pipe)
{
    if(y + height > pipe->GetY() + pipe->gap || y < pipe->GetY() - pipe->gap)
    {
        network->Fitness = Container::Score;
        dead = true;
    }
}

void Bird::Update()
{
    y -= Jumpheight;
    Jumpheight -= gravity;
    if (y < -Container::WindowHeight/2 || y+height/2 > Container::WindowHeight / 2)
    {
        network->Fitness = Container::Score;
        dead = true;
    }
}

void Bird::Update(double a, double b)
{
    vector<double> input = { a, b, (double)Jumpheight };
    double i = network->Evaluate(input)[0];
    if (i > 0.5) Jump();
    Update();
}

int Bird::widht;
int Bird::height;
int Bird::x;

bool Bird::IsDead()
{
    return dead;
}

   

