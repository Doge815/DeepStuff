#pragma once

#include "Activation.hpp"

class LayerShape
{
    public:
        int Size;
        double Multiplier;
        Activation* Function;
        LayerShape(Activation* func, int size, double multiplier);

};

LayerShape::LayerShape(Activation* func, int size, double multiplier)
{
    Size = size;
    Function = func;
    Multiplier = multiplier;
}