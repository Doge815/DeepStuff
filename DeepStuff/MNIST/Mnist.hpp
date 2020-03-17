#pragma once
#define ImageSize 28
#define SizeMultiplier 20
#define Size ImageSize * SizeMultiplier

#include "SFML/Graphics.hpp"

#include "../NeuralNetwork/BaseNetwork/Network.hpp"
#include "../NeuralNetwork/Base/NetworkShape.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetwork.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetworkCollection.hpp"
#include "Reader/mnist_reader.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>

int Skip = 100;

class Mnist
{
public:
	static mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset;

	static Network* CreateAverageReader(bool verbosity = true);
	static void NetworkTester(Network network);
	static void RecognizeInput(Network network);
	static void ConsoleOutput(int* CurrentIteration, int* expectedOutput, int* output, double* error, int* detected, int* detectedFrom, vector<double>* outputVector);
	static void RenderImage(sf::RenderWindow* window, vector<uint8_t> image);
};

Network* Mnist::CreateAverageReader(bool verbosity)
{
	std::vector<LayerShape> size = { LayerShape((Activation*)(new ReLU()), 784, 0.001),
									 LayerShape((Activation*)(new ReLU()), 800, 0.001),
									 LayerShape((Activation*)(new Sigmoid()), 10, 0.001) };

	NetworkShape shape = NetworkShape(size);

	BackPropagateNetworkCollection collection = BackPropagateNetworkCollection(1, shape, 0.0001);
	BackPropagateNetwork* network = dynamic_cast<BackPropagateNetwork*>(collection.GetNetworks()[0]);
	
	int detected = 0;
	for (int i = 0; true; i++)
	{
		if (i == dataset.training_images.size())
		{
			i = 0;
		}
		vector<uint8_t> rawInput = dataset.training_images[i];
		vector<double> input(rawInput.begin(), rawInput.end());

		vector<double> outputVector = network->Evaluate(input);

		int output = -1;
		double outputVal = -1;
		for (int u = 0; u < outputVector.size(); u++)
		{
			if (outputVector[u] > outputVal)
			{
				outputVal = outputVector[u];
				output = u;
			}
		}
		int expectedOutput = dataset.training_labels[i];

		vector<double> expected = vector<double>();
		for (int u = 0; u < outputVector.size(); u++)
		{
			expected.push_back(0);
		}

		expected[expectedOutput] = 1;
		if (expectedOutput == output)
		{
			detected++;
		}

		double error = network->Learn(input, expected);
		if (i % Skip == 0)
		{
			if (verbosity)
			{
				ConsoleOutput(&i, NULL, NULL, NULL, &detected, &Skip, NULL);
			}
			if ((detected / (double)Skip) >= 0.90)
			{
				if (verbosity)
				{
					std::cout << "\033[2J\033[1;1H";
				}
				return network;
			}
			if ((detected / (double)Skip) >= 0.85)
			{
				network->Step = 0.0000001;
			}
			detected = 0;
		}
	}
}

void Mnist::RecognizeInput(Network network)
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Size, Size), "Mnist", sf::Style::Titlebar | sf::Style::Close);
	vector<uint8_t> image = vector<uint8_t>(ImageSize * ImageSize);
	
	for (size_t i = 0; i < ImageSize * ImageSize; i++)
	{
		image[i] = 0;
	}

	while (true)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(*window);
			size_t y = pos.y / SizeMultiplier;
			size_t x = pos.x / SizeMultiplier;
			image[ImageSize*y + x] = 255;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			for (size_t i = 0; i < ImageSize * ImageSize; i++)
			{
				image[i] = 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			vector<double> input(image.begin(), image.end());

			vector<double> outputVector = network.Evaluate(input);

			int output = -1;
			double outputVal = -1;
			for (int u = 0; u < outputVector.size(); u++)
			{
				if (outputVector[u] > outputVal)
				{
					outputVal = outputVector[u];
					output = u;
				}
			}
			ConsoleOutput(NULL, NULL, &output, NULL, NULL, NULL, &outputVector);
		}
		RenderImage(window, image);
	}
}

void Mnist::NetworkTester(Network network)
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Size, Size), "Mnist", sf::Style::Titlebar | sf::Style::Close);
	
	int detected = 0;
	int detectedFrom = 0;
	for (int i = 0; true; i++)
	{
		if (i == dataset.test_images.size())
		{
			i = 0;
		}
		vector<uint8_t> rawInput = dataset.test_images[i];
		vector<double> input(rawInput.begin(), rawInput.end());

		vector<double> outputVector = network.Evaluate(input);

		int output = -1;
		double outputVal = -1;
		for (int u = 0; u < outputVector.size(); u++)
		{
			if (outputVector[u] > outputVal)
			{
				outputVal = outputVector[u];
				output = u;
			}
		}
		int expectedOutput = dataset.test_labels[i];

		detectedFrom++;
		if (output == expectedOutput)
			detected++;
		
		ConsoleOutput(&i, &expectedOutput, &output, NULL, &detected, &detectedFrom, &outputVector);
		RenderImage(window, rawInput);
		getchar();
	}
}

mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> Mnist::dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>();

void Mnist::ConsoleOutput(int* CurrentIteration, int* expectedOutput, int* output, double* error, int* detected, int* detectedFrom, vector<double>* outputVector)
{
	std::cout << "\033[2J\033[1;1H";
	if(CurrentIteration != NULL)
		std::cout << "image number: " + to_string(*CurrentIteration) << std::endl;
	if (expectedOutput!= NULL)
		std::cout << "expected: " + to_string(*expectedOutput) << std::endl;
	if (output!= NULL)
		std::cout << "detected: " + to_string(*output) << std::endl;
	if(error != NULL)
		std::cout << "error: " + to_string(*error) << std::endl;
	if (detected != NULL && detectedFrom != NULL)
	{
		std::cout << "correctly recognized images: " << std::setfill('0') << std::setw((int)floor(log10(*detectedFrom)) + 1) << *detected;
		std::cout << "/" + to_string(*detectedFrom) << std::endl << std::endl;
	}

	if (outputVector != NULL)
	{
		vector<size_t> index(outputVector->size());
		iota(index.begin(), index.end(), 0);
		stable_sort(index.begin(), index.end(),
			[outputVector](size_t i1, size_t i2) {return (*outputVector)[i1] > (*outputVector)[i2]; });

		for (int u = 0; u < outputVector->size(); u++)
		{
			std::cout << "number: " + to_string(index[u]) + "    probability: " << std::setfill('0') << std::setw(3) << (int)round((*outputVector)[index[u]] * 100);
			std::cout << "%" << std::endl;
		}
	}
}

void Mnist::RenderImage(sf::RenderWindow* window, vector<uint8_t> image)
{
	sf::VertexArray pointmap(sf::Points, image.size() * SizeMultiplier * SizeMultiplier);
	for (int i = 0; i < image.size(); i++)
	{
		int x = i % ImageSize;
		int y = (i - x) / ImageSize;
		sf::Color color = sf::Color(image[i], image[i], image[i]);
		for (int u = 0; u < SizeMultiplier; u++)
		{
			for (int o = 0; o < SizeMultiplier; o++)
			{
				pointmap[i * SizeMultiplier * SizeMultiplier + u * SizeMultiplier + o].position = sf::Vector2f(x * SizeMultiplier + u, y * SizeMultiplier + o);
				pointmap[i * SizeMultiplier * SizeMultiplier + u * SizeMultiplier + o].color = color;
			}
		}
	}
	window->clear(sf::Color::Black);
	window->draw(pointmap);
	window->display();
}