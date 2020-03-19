#pragma once

#include "../Base/NetworkShape.hpp"

#include "../BaseNetwork/NetworkCollection.hpp"

#include "EvolutionNetwork.hpp"

#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct EvolutionProperties
{
	double SurvivalRate;
	double MaxEvolution;
	EvolutionProperties() { SurvivalRate = 0.2; MaxEvolution = 1.3; }
	EvolutionProperties(int survivalRate, double maxEvolution) { SurvivalRate = survivalRate; MaxEvolution = maxEvolution; }
};


class EvolutionCollection : public NetworkCollection
{
private:
	vector<EvolutionNetwork*> nets;
	EvolutionProperties props;
public:
	EvolutionCollection();
	EvolutionCollection(int amount, NetworkShape shape, EvolutionProperties Properties);
	vector<Network*> GetNetworks() override;
	void Evolve();
};

EvolutionCollection::EvolutionCollection()
{

}

EvolutionCollection::EvolutionCollection(int amount, NetworkShape shape, EvolutionProperties properties)
{
	props = properties;
	nets = vector<EvolutionNetwork*>();

	for (int i = 0; i < amount; i++)
	{
		nets.push_back(new EvolutionNetwork(shape));
	}
}

void EvolutionCollection::Evolve()
{
	std::sort(nets.begin(), nets.end());

	vector<EvolutionNetwork*> TheChosenOnes(nets.begin(), nets.begin() + (props.SurvivalRate * nets.size()));

	int size = nets.size();
	nets.clear(); //Todo: collect

	for (int i = 0; i < 1 / props.SurvivalRate; i++)	//Todo: fix rounds
	{
		for (int u = 0; u < ceil(size / props.SurvivalRate); u++)
		{
			nets.push_back(TheChosenOnes[i]->DeepCopy());
		}
	}

	for (int i = 0; i < nets.size(); i++)
	{
		double rand = (((double)std::rand()) / RAND_MAX * 2 - 1) * (props.MaxEvolution - 1) + 1;
		nets[i]->Mutate(rand);
	}
}

vector<Network*> EvolutionCollection::GetNetworks()
{
	vector<Network*> net (nets.begin(), nets.end());
	return net;
}