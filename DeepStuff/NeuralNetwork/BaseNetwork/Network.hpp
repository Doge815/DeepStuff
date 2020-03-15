#pragma once

#include "Layer.hpp"

#include "../../Extensions/Extensions.hpp"

#include <vector>
#include<string>
#include<fstream>

using namespace std;

class Network
{
protected:
	vector<Layer*> Layers;
public:
	virtual vector<double> Evaluate(vector<double> values);

	static Network Deserialize(string path);
	void Serialize(string path);
};

vector<double> Network::Evaluate(vector<double> input)
{
	vector<double> current = input;

	for (int i = 0; i < Layers.size(); i++)
	{
		current = Layers[i]->Evaluate(current);
	}

	return current;
}

void Network::Serialize(string path)
{
	string flat = "";
	flat += to_string(Layers.size()) + "\n";
	for (int i = 0; i < Layers.size(); i++)
	{
		vector<vector<double>> w = Layers[i]->GetWeights();
		flat += to_string(Layers[i]->OutputSize) + "|" + to_string(Layers[i]->InputSize) + "|" + Layers[i]->Function->ToString() + "\n";
		for (int u = 0; u < Layers[i]->OutputSize; u++)
		{
			for (int o = 0; o < Layers[i]->InputSize; o++)
			{
				flat += to_string(w[u][o]) + "|";
			}
			flat += "\n";
		}
	}

	ofstream file;
	file.open(path, ios::trunc);
	file << flat;
	file.close();
}

Network Network::Deserialize(string path)
{
	Network n = Network();
	try
	{
		n.Layers = vector<Layer*>();

		ifstream file;
		file.open(path);
		string buffer;

		getline(file, buffer);
		int LayerAmount = stoi(buffer);

		for (int i = 0; i < LayerAmount; i++)
		{
			vector<vector<double>> weights = vector<vector<double>>();
			getline(file, buffer);
			vector<string> buff = Split(buffer, '|');
			int OutputSize = stoi(buff[0]);
			int InputSize = stoi(buff[1]);
			Activation* func = (buff[2] == "Sigmoid") ? ((Activation*)new Sigmoid()) : ((Activation*)new ReLU());

			for (int i = 0; i < OutputSize; i++)
			{
				vector<double> neuron = vector<double>();
				getline(file, buffer);
				vector<string> neuronbuff = Split(buffer, '|');
				for (int o = 0; o < InputSize; o++)
				{
					neuron.push_back(stod(neuronbuff[o]));
				}
				weights.push_back(neuron);
			}
			Layer p = Layer::Deserialize(weights, InputSize, OutputSize, func);
			n.Layers.push_back(&p);
		}
	}
	catch(const std::exception & e)
	{

	}
}