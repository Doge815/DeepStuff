#pragma once

#include "Activation.hpp"

class LayerShape
{
public:
	int LayerSize;
	double Multiplier;
	Activation* Function;
	LayerShape(Activation* func, int size, double multiplier);
};

LayerShape::LayerShape(Activation* func, int size, double multiplier)
{
	LayerSize = size;
	Function = func;
	Multiplier = multiplier;
}