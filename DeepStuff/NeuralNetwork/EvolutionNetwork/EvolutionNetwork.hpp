#pragma once

#include "../Base/NetworkShape.hpp"
#include "../BaseNetwork/Network.hpp"
#include "EvolutionLayer.hpp"

class EvolutionNetwork : public Network
{
private:
	EvolutionNetwork();
public:
	double Fitness;
	EvolutionNetwork(NetworkShape shape);
	EvolutionNetwork* DeepCopy();
	void Mutate(double MutationRate);
	bool operator < (const EvolutionNetwork& other) const { return Fitness < other.Fitness; }
};

EvolutionNetwork::EvolutionNetwork()
{
	Fitness = 0;
}

EvolutionNetwork::EvolutionNetwork(NetworkShape shape)
{
	Fitness = 0;
	Layers = vector<Layer*>();

	for (int i = 0; i < shape.GetShapes().size() - 1; i++)
	{
		Layers.push_back(new EvolutionLayer(shape.GetShapes()[i].LayerSize, shape.GetShapes()[(int64_t)i + 1].LayerSize, shape.GetShapes()[(int64_t)i + 1].Function, shape.GetShapes()[(int64_t)i + 1].Multiplier));
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

EvolutionNetwork* EvolutionNetwork::DeepCopy() //Todo: use copy constructor instead
{
	EvolutionNetwork* copy = new EvolutionNetwork();
	copy->Fitness = Fitness;
	for (int i = 0; i < Layers.size(); i++)
	{
		EvolutionLayer* l = dynamic_cast<EvolutionLayer*>(Layers[i]);
		copy->Layers.push_back(l->DeepCopy());
	}
	return copy;
}