#pragma once

#include <unordered_map>

using namespace std;

template <typename I>
struct ArrayWrapper
{
public:
	I* values;
	uint32_t size;

    ArrayWrapper(uint32_t size);
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
        for (result_type i = 0; i < a.size; i++)
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
    QTable(uint32_t size, ArrayWrapper<I>* values);
};

template <typename I>
QTable<I>::QTable(uint32_t size, ArrayWrapper<I>* values)
{
    /*
    int p_size = 1;
    for (int i = 0; i < size; i++)
    {
        p_size *= values->size;
    }

    I* comb = malloc(p_size * sizeof(I*));

    for (int i = 0; i < size; i++)
    {
        p_size /= values->size;

        for (int j = 0; j < values->size; j++)
        {
            for (int k = 0; k < p_size; k++)
            {
                int pos = 
            }
        }
    }
    */
    int blocksize = size * sizeof(ArrayWrapper<I>);
    int blocks = 1;
    for (int i = 0; i < size; i++)
    {
        p_size *= values->size;
    }

    ArrayWrapper<int> pos = ArrayWrapper(size);
    for (int i = 0; i < size; i++)
    {
        pos->values[i] = 0;
    }

    for (int i = 0; i < blocks; i++)
    {

    }
}