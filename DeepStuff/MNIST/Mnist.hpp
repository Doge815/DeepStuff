#pragma once
#define ImageSize 28
#define SizeMultiplier 20
#define Size ImageSize * SizeMultiplier
#define Skip 100

#include "SFML/Graphics.hpp"

#include "../NeuralNetwork/Base/NetworkShape.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetwork.hpp"
#include "../NeuralNetwork/BackPropagateNetwork/BackPropagateNetworkCollection.hpp"
#include "Reader/mnist_reader.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

void RenderImage(sf::RenderWindow* window, vector<uint8_t> image);

class Mnist
{
    public:
        static void Mnister();
};

void Mnist::Mnister()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Size, Size), "Mnist detector", sf::Style::Titlebar | sf::Style::Close);

    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>();

    std::vector<LayerShape> size = {	LayerShape((Activation*)(new ReLU()), 784),
										LayerShape((Activation*)(new ReLU()), 800), 
										LayerShape((Activation*)(new Sigmoid()), 10)};

	NetworkShape shape = NetworkShape(size);

	BackPropagateNetworkCollection collection = BackPropagateNetworkCollection(1, shape);
	BackPropagateNetwork network = dynamic_cast<BackPropagateNetwork&>(*collection.GetNetworks()[0]);
	
    int detected = 0;
    for(int i = 0; true; i++)
	{
        if (i == dataset.training_images.size())
        {
            i = 0;
        }
        vector<uint8_t> rawInput = dataset.training_images[i];
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
        if (expectedOutput == output)
        {
            detected++;
        }

        double error = network.Learn(input, expected);

        if (i % Skip == 0)
        {
            std::cout << "\033[2J\033[1;1H";
            std::cout << "image number: " + to_string(i) << std::endl << std::endl;
            std::cout << "expected: " + to_string(expectedOutput) << std::endl;
            std::cout << "detected: " + to_string(output) << std::endl;
            std::cout << "error: " + to_string(error) << std::endl;
            std::cout << "correctly recognized images: " << std::setfill('0') << std::setw(3) << detected;
            std::cout << "/" + to_string(Skip) << std::endl << std::endl;

            for (int u = 0; u < outputVector.size(); u++)
            {
                std::cout << "number: " + to_string(u) + "; probability: " + to_string(outputVector[u]) << std::endl;
            }
            RenderImage(window, rawInput);
            detected = 0;
            //getchar();
        }
        
        
	}
}

void RenderImage(sf::RenderWindow* window, vector<uint8_t> image)
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