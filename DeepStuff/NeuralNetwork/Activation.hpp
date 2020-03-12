#include <vector>

using namespace std;

class ActivationFunction
{
    public:
        static vector<double> Activate(vector<double> value);
        static vector<double> ActivationDerivative(vector<double> value);
        static vector<double> ActivationInverse(vector<double> value);
};

class ReLu : public ActivationFunction
{
    public:
        static vector<double> Activate(vector<double> value);
        static vector<double> ActivationDerivative(vector<double> value);
        static vector<double> ActivationInverse(vector<double> value); 

};

vector<double> ReLu::Activate(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(value[i] > 0 ? value[i] : 0);
    }
    return output;
}

vector<double> ReLu::ActivationDerivative(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(value[i] > 0 ? 1 : 0);
    }
    return output;
}

vector<double> ReLu::ActivationInverse(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(value[i]);
    }
    return output;
}