#pragma once

#include "../Base/NeuralNetworkCollection.hpp"
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
        vector<INetwork*> GetNetworks() override;
        void Evolve();
};

BackPropagateNetworkCollection::BackPropagateNetworkCollection(int amount, NetworkShape shape, double Step)
{
    nets = vector<BackPropagateNetwork*>();
    for(int i = 0; i < amount; i++)
    {
        nets.push_back(new BackPropagateNetwork(shape, Step));
    }
}

void BackPropagateNetworkCollection::Evolve()
{
}

vector<INetwork*> BackPropagateNetworkCollection::GetNetworks()
{
    vector<INetwork*> net(nets.begin(), nets.end());
    return net;
}