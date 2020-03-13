#pragma once
#define Size 28 * 20

#include "SFML/Graphics.hpp""

#include "../NeuralNetwork/Base/NetworkShape.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetwork.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetworkCollection.hpp"
#include "Reader/mnist_reader.hpp"

#include <vector>
#include <string>
#include <iostream>

class Mnist
{
    public:
        static void Mnister();
};

void Mnist::Mnister()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Size, Size), "FlappyDeep2", sf::Style::Titlebar | sf::Style::Close);

    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>();

    std::vector<LayerShape> size = {	LayerShape((Activation*)(new ReLU()), 784),
										LayerShape((Activation*)(new ReLU()), 800), 
										LayerShape((Activation*)(new Sigmoid()), 10)};

	NetworkShape shape = NetworkShape(size);

	BackPropagateNetworkCollection collection = BackPropagateNetworkCollection(1, shape);
	BackPropagateNetwork network = dynamic_cast<BackPropagateNetwork&>(*collection.GetNetworks()[0]);
	
    for(int i = 0; i < dataset.training_images.size(); i++)
	{
        vector<uint8_t> rawInput = dataset.test_images[i];
        vector<double> input(rawInput.begin(), rawInput.end());

        vector<double> outputVector = network.Evaluate(input);

        int output = -1;
        double outputVal = -1;
        for (int u = 0; u < outputVector.size(); u++)
        {
            if(outputVector[u] > outputVal)
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

        double error = network.Learn(input, expected);

        if (i % 100 == 0 || true)
        {
            std::cout << "\033[2J\033[1;1H";
            std::cout << "image number: " + to_string(i) << std::endl << std::endl;
            std::cout << "expected: " + to_string(expectedOutput) << std::endl;
            std::cout << "detected: " + to_string(output) << std::endl;
            std::cout << "error: " + to_string(error) << std::endl << std::endl;

            for (int u = 0; u < outputVector.size(); u++)
            {
                std::cout << "number: " + to_string(u) + "; probability: " + to_string(outputVector[u]) << std::endl;
            }

            getchar();
        }
        
        
	}
}