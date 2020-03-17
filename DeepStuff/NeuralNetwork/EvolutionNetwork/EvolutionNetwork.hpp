#pragma once

#include "../BaseNetwork/Network.hpp"
#include "EvolutionLayer.hpp"

class EvolutionNetwork : public Network
{
private:

public:
	double Fitness;
	EvolutionNetwork* DeepCopy();
	void Mutate(double MutationRate);
	bool operator < (const EvolutionNetwork& other) const { return Fitness < other.Fitness; }
};

void EvolutionNetwork::Mutate(double MutationRate)
{
	for (int i = 0; i < Layers.size(); i++)
	{
		EvolutionLayer* l = dynamic_cast<EvolutionLayer*>(Layers[i]);
		l->Mutate(MutationRate);
	}
}