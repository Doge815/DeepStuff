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
	vector<double> Evaluate(vector<double> val);
	virtual vector<double> Train(vector<double> errorSignal, vector<double> Iout, vector<double> Oin, double step) = 0;
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