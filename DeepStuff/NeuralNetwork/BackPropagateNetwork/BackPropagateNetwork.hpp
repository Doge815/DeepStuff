#pragma once

#include "../Base/Activation.hpp"
#include "../BaseNetwork/Layer.hpp"

#include "../BaseNetwork/Network.hpp"
#include "../Base/NetworkShape.hpp"

#include "BackPropagateLayer.hpp"

#include <vector>
#include <math.h>

using namespace std;

class BackPropagateNetwork : public Network
{
public:
	double Step;
	BackPropagateNetwork(NetworkShape shape, double step = 0.0001);

	double Learn(vector<double> input, vector<double> expected);
};

BackPropagateNetwork::BackPropagateNetwork(NetworkShape shape, double step)
{
	Step = step;
	Layers = vector<Layer*>();

	for (int i = 0; i < shape.GetShapes().size() - 1; i++)
	{
		Layers.push_back(new BackPropagateNetworkLayer(shape.GetShapes()[i].LayerSize, shape.GetShapes()[(int64_t)i + 1].LayerSize, shape.GetShapes()[(int64_t)i + 1].Function, shape.GetShapes()[(int64_t)i + 1].Multiplier));
	}
}

double BackPropagateNetwork::Learn(vector<double> input, vector<double> expected)
{
	vector<vector<double>> Iout = vector<vector<double>>();
	Iout.push_back(input);
	for (int i = 0; i < Layers.size(); i++)
	{
		Iout.push_back(Layers[i]->Evaluate(Iout[i]));
	}

	vector<double> errorSignal = vector<double>();
	double error = 0;

	for (int i = 0; i < Iout[Layers.size()].size(); i++)
	{
		double absoluteError = expected[i] - Iout[Layers.size()][i];
		error += absoluteError * absoluteError;
		errorSignal.push_back(absoluteError);
	}

	error /= input.size();

	for (int u = (int)Layers.size() - 1; u >= 0; u--)
	{
		vector<double> b = Layers[u]->Function->ActivationInverse(Iout[(int64_t)u + 1]);
		BackPropagateNetworkLayer* l = dynamic_cast<BackPropagateNetworkLayer*>(Layers[u]);
		errorSignal = l->Train(errorSignal, Iout[u], b, Step);
	}

	return error;
}