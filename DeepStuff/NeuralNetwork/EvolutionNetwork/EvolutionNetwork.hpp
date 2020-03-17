#pragma once

#include "../Base/NetworkShape.hpp"
#include "../BaseNetwork/Network.hpp"
#include "EvolutionLayer.hpp"

class EvolutionNetwork : public Network
{
private:

public:
	double Fitness;
	EvolutionNetwork(NetworkShape shape);
	EvolutionNetwork* DeepCopy();
	void Mutate(double MutationRate);
	bool operator < (const EvolutionNetwork& other) const { return Fitness < other.Fitness; }
};

EvolutionNetwork::EvolutionNetwork(NetworkShape shape)
{
	Layers = vector<Layer*>();

	for (int i = 0; i < shape.GetShapes().size() - 1; i++)
	{
		Layers.push_back(new EvolutionLayer(shape.GetShapes()[i].Size, shape.GetShapes()[i + 1].Size, shape.GetShapes()[i + 1].Function, shape.GetShapes()[i + 1].Multiplier));
	}
}

void EvolutionNetwork::Mutate(double MutationRate)
{
	for (int i = 0; i < Layers.size(); i++)
	{
		EvolutionLayer* l = dynamic_cast<EvolutionLayer*>(Layers[i]);
		l->Mutate(MutationRate);
	}
}