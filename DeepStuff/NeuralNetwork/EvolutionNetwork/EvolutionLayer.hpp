#pragma once

#include "../BaseNetwork/Layer.hpp"

class EvolutionLayer : public Layer
{
public:
	void Mutate(double MutationRate);
};

void EvolutionLayer::Mutate()
{

}