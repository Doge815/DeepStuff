#pragma once

#include "vector"
#include <stdexcept>

#include "LayerShape.hpp"

using namespace std;

class NetworkShape
{
    private:
        vector<LayerShape> layerShapes;

    public:
        NetworkShape(vector<LayerShape> shapes);
        vector<LayerShape> GetShapes();
};

NetworkShape::NetworkShape(vector<LayerShape> shapes)
{
    if(shapes.size() < 2) 
    {
        throw std::invalid_argument("s needs at least 2 layers");
    }
    layerShapes = shapes;
}

vector<LayerShape> NetworkShape::GetShapes()
{
    return layerShapes;
}