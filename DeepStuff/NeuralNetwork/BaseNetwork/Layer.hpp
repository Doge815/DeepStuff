#pragma once

#include <vector>

using namespace std;

class Layer
{
protected:
	vector<vector<double>> Weights;
	int InputSize;
	int OutputSize;
public:
	virtual vector<double> Evaluate(vector<double> val);

	Activation* Function = NULL;
};

vector<double> Layer::Evaluate(vector<double> val)
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