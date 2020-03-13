#pragma once

#include "../NeuralNetwork/Base/LayerShape.hpp"
#include "../NeuralNetwork/Base/NetworkShape.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetwork.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetworkCollection.hpp"

#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

#define maxValue 10

class Approximation
{
public:
	static void Approximator();

};

void Approximation::Approximator()
{
	std::vector<LayerShape> size = {	LayerShape((Activation*)(new ReLU()), 3, 1),
										LayerShape((Activation*)(new ReLU()), 5, 1), 
										LayerShape((Activation*)(new ReLU()), 1, 1)};
	NetworkShape shape = NetworkShape(size);

	BackPropagateNetworkCollection collection = BackPropagateNetworkCollection(1, shape);
	BackPropagateNetwork network = dynamic_cast<BackPropagateNetwork&>(*collection.GetNetworks()[0]);
	
	while (true)
	{
		vector<double> input = vector<double>();
		input.push_back((double)rand() / RAND_MAX * 5);
		input.push_back((double)rand() / RAND_MAX * 5);
		input.push_back((double)rand() / RAND_MAX * 5);

		double inputSum = input[0] + input[1] + input[2];
		vector<double> outputVector = network.Evaluate(input);
		double output = outputVector[0];
		double deviation = inputSum / output;
		std::cout << "deviation: " + to_string(deviation) << std::endl;

		vector<double> expected = { inputSum };
		network.Learn(input, expected);
	}
}