#include "../Approximation/Approximation.hpp"
#include "../MNIST/Mnist.hpp"
#include "../NeuralNetwork/BaseNetwork/Network.hpp"

int main()
{
	//Approximation::Approximator();
	//Mnist::NetworkTester();
	(*Mnist::CreateAverageReader()).Serialize("o.utput");
	Mnist::NetworkTester(&Network::Deserialize("o.utput"));
	getchar();
	return 0;
}