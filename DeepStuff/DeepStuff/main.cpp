#include "../Approximation/Approximation.hpp"
#include "../MNIST/Mnist.hpp"
#include "../NeuralNetwork/BaseNetwork/Network.hpp"

#include<iostream>

int main()
{
	//Approximation::Approximator();
	//Mnist::NetworkTester();
	//(*Mnist::CreateAverageReader()).Serialize("o.utput");
	Network n = Network::Deserialize("o.utput");
	Mnist::NetworkTester(n);
	getchar();
	return 0;
}