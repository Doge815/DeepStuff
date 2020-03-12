#pragma once

#include "../Network.hpp"
#include "../NetworkShape.hpp"
#include "../LayerShape.hpp"
#include "BackPropagateNetworkLayer.hpp"

#include <vector>
#include <math.h>

using namespace std;

class BackPropagateNetwork : public INetwork
{
    private:

        vector<BackPropagateNetworkLayer> Layers;

    public:

        BackPropagateNetwork(NetworkShape shape);

        vector<double> Evaluate(vector<double> input) override;
        double Learn(vector<double> input, vector<double> expected);
};

BackPropagateNetwork::BackPropagateNetwork(NetworkShape shape)
{
    Layers = vector<BackPropagateNetworkLayer>();
    
    for (size_t i = 0; i < shape.GetShapes().size() - 1; i++)
    {
        Layers.push_back(BackPropagateNetworkLayer(shape.GetShapes()[i].GetSize(), shape.GetShapes()[i].GetSize(), shape.GetShapes()[i].GetFunction()));
    }
}

vector<double> BackPropagateNetwork::Evaluate(vector<double> input)
{
    vector<double> current = input;

    for (size_t i = 0; i < Layers.size(); i++)
    {
        current = Layers[i].Evaluate(current);
    }

    return current;
}

double BackPropagateNetwork::Learn(vector<double> input, vector<double> expected)
{
    vector<vector<double>> Iout = vector<vector<double>>();
    Iout.push_back(input);
    for (size_t i = 0; i < Layers.size() ; i++)
    {
        Iout.push_back(Layers[i].Evaluate(Iout[i]));
    }

    vector<double> errorSignal = vector<double>();
    double error = 0;

    for (size_t i = 0; i < Iout[Layers.size()].size(); i++)
    {
        double absoluteError = expected[i] - Iout[Layers.size()][i];
        error += absoluteError * absoluteError;
        errorSignal.push_back(absoluteError);
    }

    error /= input.size();
    

    for (int u = Layers.size() - 1; u >= 0; u--)
    {
        vector<double> b = Layers[u].Activator.ActivationInverse(Iout[u+1]);
        errorSignal = Layers[u].Train(errorSignal, Iout[u], b);
    }

    return error;
}