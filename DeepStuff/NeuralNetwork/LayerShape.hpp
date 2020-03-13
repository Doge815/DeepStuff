#pragma once

#include "Activation.hpp"

class LayerShape
{
    public:
        int Size;
        Activation* Function;
        LayerShape(Activation* func, int size);

};

LayerShape::LayerShape(Activation* func, int size)
{
    Size = size;
    Function = func;
}