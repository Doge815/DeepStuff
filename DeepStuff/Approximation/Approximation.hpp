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
	std::vector<int> size = {3, 5, 1};
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
		double deviation = 0;
		if (inputSum / output < 1)
		{
			deviation = -(output / inputSum) + 1;
		}
		else
		{
			deviation = inputSum / output - 1;
		}
		deviation--;
		std::cout << "value: " + std::to_string(inputSum) + " output: " + std::to_string(output) + " deviation " + std::to_string(deviation) << std::endl;

		vector<double> expected = { inputSum };
		network.Learn(input, expected);
	}
}

std::string to_string(double dbl)
{
	std::ostringstream strs;
	strs << dbl;
	return strs.str();
}