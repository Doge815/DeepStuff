#pragma once

#include <vector>

using namespace std;

class INetwork
{
    public:
        double Step =0;
        virtual vector<double> Evaluate(vector<double> values) =0;
        virtual double Learn(vector<double> input, vector<double> expected) = 0;
};