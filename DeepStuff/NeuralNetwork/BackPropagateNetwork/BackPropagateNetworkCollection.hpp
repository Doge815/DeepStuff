#pragma once

#include "../BaseNetwork/NetworkCollection.hpp"
#include "../Base/NetworkShape.hpp"
#include "BackPropagateNetwork.hpp"

#include<vector>
#include<cstdlib>

using namespace std;

class BackPropagateNetworkCollection : public NeuralNetworkCollection
{
	vector<BackPropagateNetwork*> nets;
	int amountOfNetworks;
public:
	BackPropagateNetworkCollection(int amount, NetworkShape shape, double Step);
	vector<Network*> GetNetworks() override;
	void Evolve();
};

BackPropagateNetworkCollection::BackPropagateNetworkCollection(int amount, NetworkShape shape, double Step)
{
	nets = vector<BackPropagateNetwork*>();
	for (int i = 0; i < amount; i++)
	{
		nets.push_back(new BackPropagateNetwork(shape, Step));
	}
}

void BackPropagateNetworkCollection::Evolve()
{
}

vector<Network*> BackPropagateNetworkCollection::GetNetworks()
{
	vector<Network*> net(nets.begin(), nets.end());
	return net;
}