#pragma once

#include "Network.hpp"

#include<vector>

using namespace std;

class NeuralNetworkCollection
{
public:
	virtual vector<Network*> GetNetworks() = 0;
	virtual void Evolve() = 0;
};