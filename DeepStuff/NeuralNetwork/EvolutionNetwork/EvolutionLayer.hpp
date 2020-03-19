#pragma once

#include "../BaseNetwork/Layer.hpp"

class EvolutionLayer : public Layer
{
public:
	EvolutionLayer(int inputSize, int outputSize, Activation* func, double WeightBaseMultiplier);
	void Mutate(double MutationRate);
	EvolutionLayer* DeepCopy();
};

void EvolutionLayer::Mutate(double MutationRate)
{
	for (int i = 0; i < OutputSize; i++)
	{
		for (int u = 0; u < InputSize; u++)
		{
			Weights[i][u] += MutationRate;
		}
	}
}

EvolutionLayer::EvolutionLayer(int inputSize, int outputSize, Activation* func, double WeightBaseMultiplier)
{
	InputSize = inputSize;
	OutputSize = outputSize;
	Function = func;

	Weights = vector<vector<double>>();
	for (int i = 0; i < outputSize; i++)
	{
		Weights.push_back(vector<double>());
		for (int j = 0; j < inputSize; j++)
		{
			Weights[i].push_back(((((double)rand()) / RAND_MAX) * 2 - 1) * WeightBaseMultiplier);
		}
	}
}

EvolutionLayer* EvolutionLayer::DeepCopy()
{
	EvolutionLayer* copy = new EvolutionLayer(InputSize, OutputSize, Function, 0);
	for (int i = 0; i < OutputSize; i++)
	{
		for (int u = 0; u < InputSize; u++)
		{
			copy->Weights[i][u] = Weights[i][u];
		}
	}
	return copy;
}