#include "../NeuralNetwork/NetworkShape.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetwork.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetworkCollection.hpp"

#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

#define maxValue 10

class Approximation
{
private:
public:
	Approximation();

};

Approximation::Approximation()
{
	std::vector<int> size = vector<int>();
	size.push_back(3);
	size.push_back(5);
	size.push_back(1);
	NetworkShape shape = NetworkShape(size);

	BackPropagateNetworkCollection collection = BackPropagateNetworkCollection(1, shape);
	BackPropagateNetwork network = dynamic_cast<BackPropagateNetwork&>(*collection.GetNetworks()[0]);
	while (true)
	{
		vector<double> input = vector<double>();
		input.push_back((double)rand() / RAND_MAX * 2 - 1);
		input.push_back((double)rand() / RAND_MAX * 2 - 1);
		input.push_back((double)rand() / RAND_MAX * 2 - 1);

		double inputSum = input[0] + input[1] + input[2];
		vector<double> outputVector = network.Evaluate(input);
		double output = outputVector[0];
		double deviation = inputSum / output;

		std::cout << "value: " + std::to_string(inputSum) + " output: " + std::to_string(output) + " deviation " + std::to_string(deviation) << std::endl;

		vector<double> expected = vector<double>();
		expected.push_back(inputSum);
		network.Learn(outputVector, expected);
	}
}

std::string to_string(double dbl)
{
	std::ostringstream strs;
	strs << dbl;
	return strs.str();
}