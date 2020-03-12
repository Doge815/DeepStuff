#include <vector>
#include "Activation.hpp"

class LayerShape
{
    private:
        ActivationFunction Function;
        int Size;
    public:
        LayerShape(ActivationFunction function, int size);
        int GetSize();
        ActivationFunction GetFunction();
};

/*
LayerShape::LayerShape(ActivationFunction function, int size)
{
    Function = function;
    Size = size;
}

int LayerShape::GetSize()
{
    return Size;
}

ActivationFunction LayerShape::GetFunction()
{
    return Function;
}*/
