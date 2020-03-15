#pragma once

#include<vector>

using namespace std;

class Layer
{
protected:
	vector<vector<double>> Weights;
public:
	int InputSize;
	int OutputSize;
	Activation* Function;
};