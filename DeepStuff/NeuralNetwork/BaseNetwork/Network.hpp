#pragma once

#include "../BackPropagateNetwork/BackPropagateNetworkLayer.hpp"
#include <vector>

using namespace std;

class Network
{
protected:
	vector<BackPropagateNetworkLayer> Layers;
public:
	double Step = 0;
	virtual vector<double> Evaluate(vector<double> values);
};

vector<double> Network::Evaluate(vector<double> input)
{
	vector<double> current = input;

	for (int i = 0; i < Layers.size(); i++)
	{
		current = Layers[i].Evaluate(current);
	}

	return current;
}