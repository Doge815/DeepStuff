#pragma once

#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class Activation
{
public:
	virtual vector<double> Activate(vector<double> value) = 0;
	virtual vector<double> ActivationDerivative(vector<double> value) = 0;
	virtual vector<double> ActivationInverse(vector<double> value) = 0;
};

class ReLU : public Activation
{
public:
	vector<double> Activate(vector<double> value);
	vector<double> ActivationDerivative(vector<double> value);
	vector<double> ActivationInverse(vector<double> value);
};

vector<double> ReLU::Activate(vector<double> value)
{
	vector<double> output = vector<double>();
	for (int i = 0; i < value.size(); i++)
	{
		output.push_back(value[i] > 0 ? value[i] : 0);
	}
	return output;
}

vector<double> ReLU::ActivationDerivative(vector<double> value)
{
	vector<double> output = vector<double>();
	for (int i = 0; i < value.size(); i++)
	{
		output.push_back(value[i] > 0 ? 1 : 0);
	}
	return output;
}

vector<double> ReLU::ActivationInverse(vector<double> value)
{
	vector<double> output = vector<double>();
	for (int i = 0; i < value.size(); i++)
	{
		output.push_back(value[i]);
	}
	return output;
}

class Sigmoid : public Activation
{
public:
	vector<double> Activate(vector<double> value);
	vector<double> ActivationDerivative(vector<double> value);
	vector<double> ActivationInverse(vector<double> value);
};

vector<double> Sigmoid::Activate(vector<double> value)
{
	vector<double> output = vector<double>();
	for (int i = 0; i < value.size(); i++)
	{
		output.push_back(1 / (1 + std::exp(-value[i])));
	}
	return output;
}

vector<double> Sigmoid::ActivationDerivative(vector<double> value)
{
	vector<double> output = vector<double>();
	for (int i = 0; i < value.size(); i++)
	{
		double y = (1 / (1 + std::exp(-value[i])));
		output.push_back(y * (1 - y));
	}
	return output;
}

vector<double> Sigmoid::ActivationInverse(vector<double> value)
{
	vector<double> output = vector<double>();
	for (int i = 0; i < value.size(); i++)
	{
		output.push_back(std::log(value[i] / (1 - value[i])));
	}
	return output;
}