#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> Split(string ToSplit, char Split)
{
    std::stringstream ss(ToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, Split))
    {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}