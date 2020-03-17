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
	int SurvivalRate;
	double MaxEvolution;
};


class EvolutionCollection : public NetworkCollection
{
private:
	vector<EvolutionNetwork*> nets;
	EvolutionProperties props;
public:
	
	EvolutionCollection(int amount, NetworkShape shape, EvolutionProperties Properties);
	vector<Network*> GetNetworks() override;
	void Evolve();
};

void EvolutionCollection::Evolve()
{
	std::sort(nets.begin(), nets.end());

	vector<EvolutionNetwork*> TheChosenOnes(nets.begin(), nets.begin() + (props.SurvivalRate / nets.size()));

	int size = nets.size();
	nets.clear(); //Todo: collect

	for (int i = 0; i < TheChosenOnes.size(); i++)	//Todo: fix rounds
	{
		for (int u = 0; u < ceil(size / props.SurvivalRate); u++)
		{
			nets.push_back(TheChosenOnes[i]->DeepCopy());
		}
	}
}