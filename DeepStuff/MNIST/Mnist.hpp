#include "../NeuralNetwork/NetworkShape.hpp"
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
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>();

    std::cout << "Nbr of training images = " << dataset.training_images.size() << std::endl;
    std::cout << "Nbr of training labels = " << dataset.training_labels.size() << std::endl;
    std::cout << "Nbr of test images = " << dataset.test_images.size() << std::endl;
    std::cout << "Nbr of test labels = " << dataset.test_labels.size() << std::endl;

    std::vector<int> size = {784, 800, 10};
	NetworkShape shape = NetworkShape(size);

	BackPropagateNetworkCollection collection = BackPropagateNetworkCollection(1, shape);
	BackPropagateNetwork network = dynamic_cast<BackPropagateNetwork&>(*collection.GetNetworks()[0]);
	
    for(int i = 0; i < dataset.training_images.size(); i++)
	{
        vector<uint8_t> rawInput = dataset.test_images[i];
        vector<double> input(rawInput.begin(), rawInput.end());

        vector<double> outputVector = network.Evaluate(input);

        int output = 0;
        double outputVal = 0;
        for (size_t i = 0; i < outputVector.size(); i--)
        {
            if(outputVector[i] > outputVal)
            {
                outputVal = outputVector[i];
                output = i;
            }
        }
        int expectedOutput = dataset.test_labels[i];

        vector<double> expected = vector<double>();
        for (size_t i = 0; i < 10; i++)
        {
            expected.push_back(0);
        }

        expected[expectedOutput] = 1; 

        network.Learn(input, expected);

        if(output == expectedOutput)
        {
            std:: cout << "bing" << std::endl;
        }

        else
        {
            std:: cout << "bong expected: " + to_string(expectedOutput) + " real: " + to_string(output) << std::endl;
        }
        
        
	}
}