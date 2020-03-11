#pragma once

#include <vector>

using namespace std;

class INetwork
{
    public:
        virtual vector<double> Evaluate(vector<double> values) =0;
};