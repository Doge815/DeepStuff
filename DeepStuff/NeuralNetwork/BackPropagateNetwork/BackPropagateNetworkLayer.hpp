#pragma once

#define step 0.000001

#include <vector>
#include <stdexcept>
#include <math.h>

#include "../Activation.hpp"

using namespace std;

//enum LayerType {Hidden, Input, Output};

class BackPropagateNetworkLayer
{
    private:

        vector<vector<double>> Weights;
    
    public:

        int InputSize;
        int OutputSize;

        BackPropagateNetworkLayer(int inputSize, int outputSize, ActivationFunction function);
        vector<double> Evaluate(vector<double> val);
        vector<double> Train(vector<double> errorSignal, vector<double> Iout, vector<double> Oin);
        ActivationFunction Activator;

        
};

BackPropagateNetworkLayer::BackPropagateNetworkLayer(int inputSize, int outputSize, ActivationFunction function)
{
    InputSize = inputSize;
    OutputSize = outputSize;
    Activator = function;

    Weights = vector<vector<double>>();
    for (size_t i = 0; i < outputSize; i++)
    {
        Weights.push_back(vector<double>());
        for (size_t j = 0; j < inputSize; j++)
        {
            Weights[i].push_back((((double)rand()) / RAND_MAX));
        }
    }
}

vector<double> BackPropagateNetworkLayer::Evaluate(vector<double> val)
{
    if (val.size() != InputSize)
    {
        throw invalid_argument("vector val has wrong size");
    }
    vector<double> output = vector<double>();

    for (int i = 0; i < OutputSize; i++)
    {
        double accumulator = 0;

        for (int j = 0; j < InputSize; j++)
        {
            double t = val[j];
            double u = Weights[i][j];
            accumulator += t * u;
        }

        output.push_back(accumulator);
    }

    return Activator.Activate(output);
}

vector<double> BackPropagateNetworkLayer::Train(vector<double> errorSignal, vector<double> Iout, vector<double> Oin)
{
    if (Iout.size() != InputSize)
    {
        throw invalid_argument("vector Iout has wrong size");
    }
    if (Oin.size() != OutputSize)
    {
        throw invalid_argument("vector Oin has wrong size");
    }
    vector<double> dEdOout = errorSignal;
    vector<double> dOoutdOin = Activator.ActivationDerivative(Oin);
    vector<double> dOindW = Iout;

    for (size_t i = 0; i < InputSize; i++)
    {
        for (size_t j = 0; j < OutputSize; j++)
        {
            double errorGradient = dEdOout[j] * dOoutdOin[j] * dOindW[i];
            Weights[j][i] += step * errorGradient;
        }
    }

    vector<double> dEdIout = vector<double>();
    for (size_t i = 0; i < InputSize; i++)
    {
        double accumulator = 0;

        for (size_t j = 0; j < OutputSize; j++)
        {
            accumulator += dEdOout[j] * dOoutdOin[j] * Weights[j][i];
        }

        dEdIout.push_back(accumulator);
    }
    
    return dEdIout;
}