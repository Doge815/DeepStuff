#pragma once

#include <vector>
#include <stdexcept>
#include "LayerShape.hpp"

using namespace std;

class NetworkShape
{
private:
	vector<LayerShape> layer;

public:
	NetworkShape(vector<LayerShape> s);
	vector<LayerShape> GetShapes();
};

NetworkShape::NetworkShape(vector<LayerShape> s)
{
	if (s.size() < 2)
	{
		throw std::invalid_argument("s needs at least 2 values");
	}
	layer = s;
}

vector<LayerShape> NetworkShape::GetShapes()
{
	return layer;
}