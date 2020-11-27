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
	uint32_t outputPossibillities;
	unordered_map<ArrayWrapper<I>, ArrayWrapper<double>> Table;
public:
	QTable(uint32_t size, tuple<int, int>* ranges, int32_t possibilities);
	QTable(uint32_t size, ArrayWrapper<I>* values, int32_t possibilities);
};

template <typename I>
QTable<I>::QTable(uint32_t size, ArrayWrapper<I>* values, int32_t possibillities)
{
	int blocks = 1;

	for (int i = 0; i < size; i++)
	{
		//Todo: check size > 1
		p_size *= values[i].size;
	}

	ArrayWrapper<int> pos = ArrayWrapper(size);
	for (int i = 0; i < size; i++)
	{
		pos.values[i] = 0;
	}

	ArrayWrapper<int> step = ArrayWrapper(size);
	step[size - 1] = 1;
	for (int i = size - 2; i >= 0; i--)
	{
		step[i] = step[i + 1] * values[i].size;
	}

	for (int i = 0; i < blocks; i++)
	{
		int blockpos = 0;
		pos.values[pos.size - 1]++;
		for (int j = pos.size - 1; j >= 0; j--)
		{
			if (pos[j] == values[j].size)
			{
				pos[j] = 0;
				pos[j - 1]++;
			}

			blockpos += pos[j] * step[j];
		}


		ArrayWrapper<I>* currentBlock = new ArrayWrapper<I>(size);
		for (int j = 0; j < size; j++)
		{
			currentBlock->values[j] = values[j].values[pos[j]];
		}
		ArrayWrapper<double>* propabilities = new ArrayWrapper<I>(possibillities);
		for (int j = 0; j < possibillities; j++)
		{
			propabilities->values[j] = ((double)rand() / (RAND_MAX));
		}
		Table.insert(&currentBlock, &propabilities);
	}
}

template <typename I>
QTable<I>::QTable(uint32_t size, tuple<int, int>* ranges, int32_t possibilities)
{
	ArrayWrapper<int>* values = new ArrayWrapper<I>(size);
	for (uint32_t i = 0; i < size; i++)
	{
		values[i] = ArrayWrapper<I>(get<0>(ranges[i]) - get<0>(ranges[i]) + 1)
		for (int u = get<0>(ranges[i]); u <= get<1>(ranges[i]); u++)
		{

		}
	}

	QTable(size, values, possibilities);
}