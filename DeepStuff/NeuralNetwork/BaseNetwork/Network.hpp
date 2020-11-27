#pragma once

#include "Layer.hpp"

#include "../../Extensions/Extensions.hpp"

#include <vector>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

class Network
{
private:
	Network(vector<Layer> layers);
protected:
	vector<Layer*> Layers;
public:
	Network();
	virtual vector<double> Evaluate(vector<double> values);
	virtual bool CheckNetwork();

	static Network Deserialize(string path);
	void Serialize(string path);
};

Network::Network() { }

vector<double> Network::Evaluate(vector<double> input)
{
	vector<double> current = input;

	for (int i = 0; i < Layers.size(); i++)
	{
		current = Layers[i]->Evaluate(current);
	}

	return current;
}

bool Network::CheckNetwork()
{
	for(int i = 0; i < Layers.size(); i++)
	{
		Layer* l = Layers[i];
		vector<vector<double>> weights = l->GetWeights();
		if(l->OutputSize != weights.size()) return false;
		for (int u = 0; u < l->OutputSize; u++)
		{
			if(l->InputSize != weights[u].size()) return false;
		}
	}
	return true;
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
	try
	{
		vector<Layer*> Layers = vector<Layer*>();

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
			Layer* p = new Layer(weights, InputSize, OutputSize, func);
			Layers.push_back(p);
		}

		Network n = Network();
		for (int i = 0; i < Layers.size(); i++)
		{
			n.Layers.push_back(Layers[i]);
		}
		if(n.CheckNetwork()) return n;
		throw new std::exception;
	}
	catch(const std::exception & e)
	{
		throw e;
	}
}