#pragma once

#include "../NeuralNetworkCollection.hpp"
#include "../NetworkShape.hpp"
#include "BackPropagateNetwork.hpp"

#include<vector>
#include<cstdlib>

using namespace std;

class BackPropagateNetworkCollection : public NeuralNetworkCollection
{
    vector<BackPropagateNetwork*> nets;
    int amountOfNetworks;
    public:
        BackPropagateNetworkCollection(int amount, NetworkShape shape);
        vector<INetwork*> GetNetworks() override;
        void Evolve();
};

BackPropagateNetworkCollection::BackPropagateNetworkCollection(int amount, NetworkShape shape)
{
    nets = vector<BackPropagateNetwork*>();
    for(int i = 0; i < amount; i++)
    {
        nets.push_back(new BackPropagateNetwork(shape));
    }
}

void BackPropagateNetworkCollection::Evolve()
{
    for (size_t i = 0; i < nets.size(); i++)
    {
        nets[i]->Learn();
    }
}

vector<INetwork*> BackPropagateNetworkCollection::GetNetworks()
{
    return vector<INetwork*>();
}