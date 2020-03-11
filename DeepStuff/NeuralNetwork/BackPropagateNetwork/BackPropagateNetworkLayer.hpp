#pragma once

#define step 0.01

#include <vector>
#include <stdexcept>
#include <math.h>

using namespace std;

enum LayerType {Hidden, Input, Output};

class BackPropagateNetworkLayer
{
    private:

        vector<vector<double>> Weights;
    
    public:

        int InputSize;
        int OutputSize;

        BackPropagateNetworkLayer(int inputSize, int outputSize);
        vector<double> Evaluate(vector<double> val);
        vector<double> Train(vector<double> errorSignal, vector<double> Iout, vector<double> Oin);

        vector<double> Activate(vector<double> value);
        vector<double> ActivationDerivative(vector<double> value);
        vector<double> ActivationInverse(vector<double> value);
};

BackPropagateNetworkLayer::BackPropagateNetworkLayer(int inputSize, int outputSize)
{
    InputSize = inputSize;
    OutputSize = outputSize;

    Weights = vector<vector<double>>();
    for (size_t i = 0; i < outputSize; i++)
    {
        Weights.push_back(vector<double>());
        for (size_t j = 0; j < inputSize; j++)
        {
            Weights[i].push_back((((double)rand()) / RAND_MAX) * 2 - 1);
        }
    }
}

vector<double> BackPropagateNetworkLayer::Evaluate(vector<double> val)
{
    vector<double> output = vector<double>();

    for (int i = 0; i < OutputSize; i++)
    {
        double accumulator = 0;

        for (int j = 0; j < InputSize; j++)
        {
            accumulator += val[j] * Weights[j][i];
        }

        output.push_back(accumulator);
    }

    return Activate(output);
}

vector<double> BackPropagateNetworkLayer::Train(vector<double> errorSignal, vector<double> Iout, vector<double> Oin)
{
    //Todo: size check
    vector<double> dEdOout = errorSignal;
    vector<double> dOoutdOin = ActivationDerivative(Oin);
    vector<double> dOindW = Iout;

    for (size_t i = 0; i < InputSize; i++)
    {
        for (size_t j = 0; j < OutputSize; j++)
        {
            double errorGradient = dEdOout[j] * dOoutdOin[j] * dOindW[i];
            Weights[j][i] -= step * errorGradient;
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

vector<double> BackPropagateNetworkLayer::Activate(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(fmaxf64(0, value[i]));
    }
    return output;
}

vector<double> BackPropagateNetworkLayer::ActivationDerivative(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(value[i] > 0 ? 1 : 0);
    }
    return output;
}

vector<double> BackPropagateNetworkLayer::ActivationInverse(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(value[i]);
    }
    return output;
}