#pragma once

#include "Network.hpp"

#include<vector>

using namespace std;

class NetworkCollection
{
public:
	virtual vector<Network*> GetNetworks() = 0;
};