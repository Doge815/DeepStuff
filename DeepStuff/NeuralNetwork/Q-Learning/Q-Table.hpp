#pragma once

#include <unordered_map>

using namespace std;

template <typename I>
struct ArrayWrapper
{
public:
	I* values;
	uint32_t* size;
};

template<typename I>
struct hash<ArrayWrapper<I> >
{
    typedef ArrayWrapper<I> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& a) const
    {
        hash<T> hasher;
        result_type h = 0;
        for (result_type i = 0; i < &(a->size); ++i)
        {
            h = h * 31 + hasher(a.values[i]);
        }
        return h;
    }
};

template <typename I>

class QTable
{
private:
    uint32_t inputSize;
    unordered_map<ArrayWrapper<I>, uint32_t> Table;
public:
    QTable(uint32_t size, tuple<int, int> ranges);
    QTable(uint32_t size, ArrayWrapper* values);
};