#pragma once

#include "vector"
#include <stdexcept>

using namespace std;

class NetworkShape
{
    private:
        vector<int> Size;

    public:
        NetworkShape(vector<int> s);
        vector<int> GetSize();
};

NetworkShape::NetworkShape(vector<int> s)
{
    if(s.size() < 2) 
    {
        throw std::invalid_argument("s needs at least 2 values");
    }
    Size = s;
}

vector<int> NetworkShape::GetSize()
{
    return Size;
}