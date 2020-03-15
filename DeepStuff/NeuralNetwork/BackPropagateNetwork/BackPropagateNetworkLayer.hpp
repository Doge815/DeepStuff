#pragma once

#include "../Base/Activation.hpp"

#include <vector>
#include <stdexcept>
#include <math.h>

using namespace std;

class BackPropagateNetworkLayer
{
private:

	vector<vector<double>> Weights;

public:

	int InputSize;
	int OutputSize;

	Activation* Function;

	BackPropagateNetworkLayer(int inputSize, int outputSize, Activation* func, double WeightBaseMultiplier);
	vector<double> Evaluate(vector<double> val);
	vector<double> Train(vector<double> errorSignal, vector<double> Iout, vector<double> Oin, double step);
};

BackPropagateNetworkLayer::BackPropagateNetworkLayer(int inputSize, int outputSize, Activation* func, double WeightBaseMultiplier)
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

vector<double> BackPropagateNetworkLayer::Evaluate(vector<double> val)
{
	if (val.size() != InputSize)
	{
		throw invalid_argument("vector val has wrong size");
	}
	vector<double> output = vector<double>();

	for (int i = 0; i < OutputSize; i++)
	{
		double accumulator = 0;

		for (int j = 0; j < InputSize; j++)
		{
			double t = val[j];
			double u = Weights[i][j];
			accumulator += t * u;
		}

		output.push_back(accumulator);
	}

	return Function->Activate(output);
}

vector<double> BackPropagateNetworkLayer::Train(vector<double> errorSignal, vector<double> Iout, vector<double> Oin, double step)
{
	if (Iout.size() != InputSize)
	{
		throw invalid_argument("vector Iout has wrong size");
	}
	if (Oin.size() != OutputSize)
	{
		throw invalid_argument("vector Oin has wrong size");
	}
	vector<double> dEdOout = errorSignal;
	vector<double> dOoutdOin = Function->ActivationDerivative(Oin);
	vector<double> dOindW = Iout;

	for (int i = 0; i < InputSize; i++)
	{
		for (int j = 0; j < OutputSize; j++)
		{
			double errorGradient = dEdOout[j] * dOoutdOin[j] * dOindW[i];
			Weights[j][i] += step * errorGradient;
		}
	}

	vector<double> dEdIout = vector<double>();
	for (int i = 0; i < InputSize; i++)
	{
		double accumulator = 0;

		for (int j = 0; j < OutputSize; j++)
		{
			accumulator += dEdOout[j] * dOoutdOin[j] * Weights[j][i];
		}

		dEdIout.push_back(accumulator);
	}

	return dEdIout;
}