#include "../Approximation/Approximation.hpp"
#include "../MNIST/Mnist.hpp"

int main()
{
    #if false
    Approximation::Approximator();
    #else
    Mnist::NetworkTester();
    #endif
    getchar();
    return 0;
}