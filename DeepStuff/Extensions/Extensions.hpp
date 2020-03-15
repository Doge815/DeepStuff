#pragma once

#include<string>
#include <algorithm>
#include <iterator>
#include <regex>
#include <vector>
#include<string>

using namespace std;

vector<string> Split(string ToSplit, string Split)
{
    std::vector<std::string> tokens;
    std::regex re(Split);

    std::sregex_token_iterator
        begin(ToSplit.begin(), ToSplit.end(), re),
        end;

    std::copy(begin, end, std::back_inserter(tokens));
    return tokens;
}