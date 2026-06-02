#include <cctype>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

template <typename Iterator>
void print_iter_array(Iterator *arr, std::size_t size)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << *arr[i];
		if (i + 1 < size)
			std::cout << ' ';
	}
	std::cout << '\n';
}

template <typename Container>
typename Container::iterator *get_iterator_array(Container &cont, std::size_t size)
{
	typedef typename Container::iterator iterator;

	iterator *it_array = new iterator[size];
	iterator it = cont.begin();

	for (std::size_t i = 0; i < size; ++i)
		it_array[i] = it++;
	return it_array;
}

template <typename Iterator>
void swap_pairs(Iterator *it_array, std::size_t pair_size, std::size_t pos)
{
	for (std::size_t i = pos; i < pos + pair_size; ++i)
		std::swap(it_array[i], it_array[i + pair_size]);
}

template <typename iterator>
iterator *ford_johnson_insertion(iterator *it_array, std::size_t block_size, size_t size)
{
	if (block_size == 0 || block_size >= size)
		return it_array;
	if ((size / block_size) < 3)
		return it_array;

	// Half the blocks, multiplied by the number of elements and adding the rest
	std::size_t pend_blocks = ((size / block_size) / 2);
	std::size_t pend_size = pend_blocks * block_size + (size % block_size);

	std::size_t main_i = 0;
	std::size_t pend_i = 0;
	iterator *main = new iterator[size]();
	iterator *pend = new iterator[pend_size]();

	for (size_t i = 0; i < size; i += block_size)
	{
		std::size_t block = i / block_size;
		for (size_t j = 0; j < block_size && i + j < size; j++)
		{
			if (block % 2 == 0)
				main[main_i++] = it_array[j + i];
			else
				pend[pend_i++] = it_array[j + i];
		}
	}

	for (size_t i = pend_blocks; i == 0; i--)
	{
		//TODO: Insercion y binary search
	}
}

template <typename iterator>
iterator *ford_johnson_pairs(iterator *it_array, std::size_t block_size, size_t size)
{
	if (block_size == 0 || block_size >= size)
		return it_array;

	std::size_t double_block_size = block_size * 2;

	for (size_t i = 0; i + double_block_size <= size; i += double_block_size)
	{
		if (*it_array[i + block_size - 1] > *it_array[i + double_block_size - 1])
			swap_pairs(it_array, block_size, i);
	}

	return ford_johnson_pairs(it_array, double_block_size, size);
}

template <typename Container>
typename Container::iterator *ford_johnson(Container &cont)
{
	typedef typename Container::iterator iterator;
	std::size_t size = cont.size();

	iterator *it_array = ford_johnson_pairs(
		get_iterator_array(cont, size), 1, size);
	return it_array;
}