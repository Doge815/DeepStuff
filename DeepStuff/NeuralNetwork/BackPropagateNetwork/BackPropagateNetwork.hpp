#pragma once

#include "../Base/Activation.hpp"
#include "../Base/Network.hpp"
#include "../Base/NetworkShape.hpp"
#include "BackPropagateNetworkLayer.hpp"

#include <vector>
#include <math.h>

using namespace std;

class BackPropagateNetwork : public INetwork
{
    private:

        vector<BackPropagateNetworkLayer> Layers;

    public:
        double Step;
        BackPropagateNetwork(NetworkShape shape, double step = 0.0001);

        vector<double> Evaluate(vector<double> input) override;
        double Learn(vector<double> input, vector<double> expected) override;
};

BackPropagateNetwork::BackPropagateNetwork(NetworkShape shape, double step)
{
    Step = step;
    Layers = vector<BackPropagateNetworkLayer>();
    
    for (int i = 0; i < shape.GetShapes().size() - 1; i++)
    {
        Layers.push_back(BackPropagateNetworkLayer(shape.GetShapes()[i].Size, shape.GetShapes()[i+1].Size, shape.GetShapes()[i+1].Function, shape.GetShapes()[i + 1].Multiplier));
    }
}

vector<double> BackPropagateNetwork::Evaluate(vector<double> input)
{
    vector<double> current = input;

    for (int i = 0; i < Layers.size(); i++)
    {
        current = Layers[i].Evaluate(current);
    }

    return current;
}

double BackPropagateNetwork::Learn(vector<double> input, vector<double> expected)
{
    vector<vector<double>> Iout = vector<vector<double>>();
    Iout.push_back(input);
    for (int i = 0; i < Layers.size() ; i++)
    {
        Iout.push_back(Layers[i].Evaluate(Iout[i]));
    }

    vector<double> errorSignal = vector<double>();
    double error = 0;

    for (int i = 0; i < Iout[Layers.size()].size(); i++)
    {
        double absoluteError = expected[i] - Iout[Layers.size()][i];
        error += absoluteError * absoluteError;
        errorSignal.push_back(absoluteError);
    }

    error /= input.size();
    

    for (int u = Layers.size() - 1; u >= 0; u--)
    {
        vector<double> b = Layers[u].Function->ActivationInverse(Iout[u+1]);
        errorSignal = Layers[u].Train(errorSignal, Iout[u], b, Step);
    }

    return error;
}