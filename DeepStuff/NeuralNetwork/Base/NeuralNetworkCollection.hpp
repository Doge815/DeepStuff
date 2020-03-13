#pragma once

#include "Network.hpp"

#include<vector>

using namespace std;

class NeuralNetworkCollection
{
    public:
        virtual vector<INetwork*> GetNetworks() = 0;
        virtual void Evolve() = 0;
};