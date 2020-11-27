#include "../Approximation/Approximation.hpp"
#include "../MNIST/Mnist.hpp"
#include "../FlappyDeep2/Game.hpp"
#include "../NeuralNetwork/BaseNetwork/Network.hpp"

#include<iostream>

int main()
{
	int id = 0;
	int id_sub = 0;
	std::cout << "enter a valid id and sub id" << std::endl;
	cin >> id >> id_sub;
	cout << id << id_sub << endl;

	switch (id)
	{
		case 0:
			switch(id_sub)
			{
				case 0:
				{
					new Game();
					break;
				}
				default:
					throw std::invalid_argument("");
			}
		case 1:
			switch (id_sub)
			{
			case 0:
			{
				Approximation::Approximator();
				break;
			}
			default:
				throw std::invalid_argument("");
			}
		case 2:
			switch (id_sub)
			{
			case 0:
			{
				(*Mnist::CreateAverageReader()).Serialize("o.utput");
				break;
			}
			case 1:
			{
				(*Mnist::CreateAverageNumberGenerator()).Serialize("o.utput");
				break;
			}
			case 2:
			{
				Network n = Network::Deserialize("o.utput");
				Mnist::NetworkTester(n);
				break;
			}
			case 3:
			{
				Network n = Network::Deserialize("o.utput");
				Mnist::RecognizeInput(n);
				break;
			}
			default:
				throw std::invalid_argument("");
			}
		default:
			throw std::invalid_argument("");
	}
	getchar();
	return 0;
}