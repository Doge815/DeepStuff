#include "../Approximation/Approximation.hpp"
#include "../MNIST/Mnist.hpp"
#include "../FlappyDeep2/Game.hpp"
#include "../NeuralNetwork/BaseNetwork/Network.hpp"

#include<iostream>

int main()
{
#if false
	Game g = Game();
#elif false
	Approximation::Approximator();

	#else
	//(*Mnist::CreateAverageReader()).Serialize("o.utput");
	Network n = Network::Deserialize("o.utput");
	//Mnist::RecognizeInput(n);
	Mnist::NetworkTester(n);
#endif

	getchar();
	return 0;
}