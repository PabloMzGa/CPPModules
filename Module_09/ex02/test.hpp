#include <algorithm>
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
#include <cstddef>
#include <iostream>

/**
 * @struct s_JacobstahlSeq
 * An struct containing an array with several Jacobstahl Numbers
 *
 * @param seq A fixed array for containing the numbers. It's size is 64 because
 *            65th Jacobstahl number is bigger than SIZE_MAX in 64 bits.
 * @param size Size of the sequence.
 */
struct s_JacobsthalSeq
{
	std::size_t seq[64];
	std::size_t size;
};

/**
 * @struct s_FJBlockInfo
 * An struct containing all block info required for the execution of the
 * Ford Johnson insertion part.
 *
 * @param main Pointer to the main chain.
 * @param main_size Number of elemets in the main chain.
 * @param main_blocks Number of blocks in the main chain.
 * @param pend Pointer to the pend chain.
 * @param pend_size Number of elemets in the pend chain.
 * @param pend_blocks Number of blocks in the pend chain.
 * @param block_size Number of elemets inside each block.
 * @param total_size Total number of elemets inside the original array.
 * @param inserted_blocks Number of blocks inserted in main.
 */
template <typename Iterator> struct s_FJBlockInfo
{
	Iterator *main;
	std::size_t main_size;
	std::size_t main_blocks;
	Iterator *pend;
	std::size_t pend_size;
	std::size_t pend_blocks;
	std::size_t block_size;
	std::size_t total_size;
	std::size_t inserted_blocks;
};

/**
 * @brief Builds and returns a s_jacobstahlSeq.
 *
 * @param size Number of Jacobstahl numbers required.
 *
 * @return A s_JacobsthalSeq object containing the required sequence.
 */
s_JacobsthalSeq buildJacobstahlSeq(std::size_t size)
{
	std::size_t jn;
	s_JacobsthalSeq js;
	js.size = 0;
	for (size_t n = 2; n < 64; n++)
	{
		jn = ((1LL << (n + 1)) + (n % 2 == 0 ? 1 : -1)) / 3;

		// std::cout << "jn = " << jn << " pend_size " << pend_size <<
		// std::endl;
		if (jn > size + 1)
			break;
		js.seq[js.size++] = jn - 1; // Make sequence 0 based
	}
	return js;
}
//TODO: Borrar
template <typename Iterator>
void print_iter_array(Iterator *arr, std::size_t size)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << *arr[i];
		std::cout.flush();
		if (i + 1 < size)
			std::cout << ' ';
	}
	std::cout << '\n';
}
/**
 * @brief Builds the iterator array from the original container
 *
 * @param Container Reference to the original container.
 * @param size Number of elements inside the container.
 */
template <typename Container>
typename Container::iterator *get_iterator_array(Container &cont,
                                                 std::size_t size)
{
	typedef typename Container::iterator iterator;

	iterator *it_array = new iterator[size];
	iterator it = cont.begin();

	for (std::size_t i = 0; i < size; ++i)
		it_array[i] = it++;
	return it_array;
}

/**
 * @brief Swaps two blocks inside an array
 *
 * It swap the positions of a given block with the one next to it
 *
 * @param it_array Array containing all iterators
 * @param block_size Size of the given block
 * @param pos Position inside the array of the given block
 */
template <typename Iterator>
void swap_blocks(Iterator *it_array, std::size_t block_size, std::size_t pos)
{
	for (std::size_t i = pos; i < pos + block_size; ++i)
		std::swap(it_array[i], it_array[i + block_size]);
}

/**
 * @brief Shifts a contiguous block of elements to the right inside an array.
 *
 * @warning The caller must ensure that the target positions
 *          (from_index + shift) ... (from_index + count - 1 + shift)
 *          are within the bounds of the array.
 *
 * @param arr Pointer to the array whose elements will be shifted.
 * @param from_index Index of the first element to shift.
 * @param count Number of elements to shift (size of the block).
 * @param shift Number of positions to move the block to the right.
 */
template <typename Iterator>
void shift_right(Iterator *arr, std::size_t from_index, std::size_t count,
                 std::size_t shift)
{
	if (count == 0 || shift == 0)
		return;
	for (std::size_t i = count; i > 0; --i)
		arr[from_index + i - 1 + shift] = arr[from_index + i - 1];
}

/**
 * @brief Binary search over blocks to find the insertion position.
 *
 * Searches the blocks in the interval [start_block, end_block] (inclusive),
 * comparing 'value' with the last element of each block. Returns the index of
 * the first block whose last element is >= value, or the position where the
 * block should be inserted if none matches.
 *
 * @param value       Value to compare.
 * @param info        Block metadata (sizes, main array, block size).
 * @param start_block First block to include in the search.
 * @param end_block   Last block to include in the search.
 *
 * @return Block index where 'value' should be inserted, clamped to
 *         [0, info.main_blocks].
 */
template <typename Iterator>
std::size_t
binary_search_block_pos(int value, const s_FJBlockInfo<Iterator> &info,
                        std::size_t start_block, std::size_t end_block)
{
	if (info.block_size == 0 || info.main_blocks == 0)
		return 0;

	// Max valid range clamp [0, info.main_blocks-1]
	if (start_block >= info.main_blocks)
		return info.main_blocks;
	if (end_block >= info.main_blocks)
		end_block = info.main_blocks - 1;
	if (start_block > end_block)
		return start_block;

	// right is exclusive: [left, right)
	std::size_t left = start_block;
	std::size_t right = end_block + 1;

	while (left < right)
	{
		//Safe mid calculation
		std::size_t mid = left + (right - left) / 2;

		//Last index from the mid block
		std::size_t last_index = (mid + 1) * info.block_size;
		if (last_index == 0)
			last_index = 0;
		else
			last_index = last_index - 1;

		// Out of bounds check
		if (last_index >= info.main_size)
			last_index = info.main_size == 0 ? 0 : info.main_size - 1;

		if (value <= *info.main[last_index])
			right = mid;
		else
			left = mid + 1;
	}

	return left;
}

/**
 * @brief Builds the block distribution used by the Ford–Johnson algorithm.
 *
 * Splits the input array into consecutive blocks of size 'block_size' and
 * distributes them into two arrays: 'main' and 'pend'. A block goes to 'main'
 * if it is the first block or if it is a full block located at an odd index.
 * Incomplete blocks (except block 0) always go to 'pend'.
 *
 * Elements are copied preserving their order inside each block. The function
 * also computes the number of blocks and elements assigned to each array.
 *
 * @param it_array   Pointer to the input array of iterators.
 * @param block_size Size of each block used for the distribution.
 * @param size       Total number of elements in the input array.
 *
 * @return A fully populated s_FJBlockInfo structure containing:
 *         - main / pend arrays
 *         - sizes and block counts
 *         - block_size and total_size
 *         If block_size is 0 or >= size, returns an empty structure.
 */
template <typename Iterator>
s_FJBlockInfo<Iterator> build_fj_block_info(Iterator *it_array,
                                          std::size_t block_size, size_t size)
{

	s_FJBlockInfo<Iterator> info;
	info.main = 0;
	info.pend = 0;
	info.main_size = 0;
	info.main_blocks = 0;
	info.pend_blocks = 0;
	info.pend_size = 0;
	info.block_size = block_size;
	info.total_size = size;
	info.inserted_blocks = 0;

	if (block_size == 0 || block_size >= size)
		return info;

	info.main = new Iterator[size]();
	info.pend = new Iterator[size]();

	std::size_t main_i = 0;
	std::size_t pend_i = 0;

	for (size_t i = 0; i < size; i += block_size)
	{
		std::size_t block = i / block_size;
		std::size_t current_block_size = std::min(block_size, size - i);

		bool goes_to_main = (block == 0 || block % 2 == 1);
		bool full_block = (current_block_size == block_size);

		// Incomplete blocks must go to pend
		if (!full_block && block != 0)
			goes_to_main = false;

		for (size_t j = 0; j < current_block_size; j++)
		{
			if (goes_to_main)
			{
				info.main[(main_i * block_size) + j] = it_array[i + j];
				++info.main_size;
			}
			else
			{
				info.pend[pend_i++] = it_array[i + j];
				++info.pend_size;
			}
		}

		if (goes_to_main)
			++main_i;
		else if (full_block)
			++info.pend_blocks;
	}

	info.main_blocks = main_i;

	return info;
}


template <typename Iterator>
Iterator *ford_johson_insertion(Iterator *it_array, std::size_t block_size,
                                size_t size)
{
	if (block_size == 0 || block_size >= size /*|| size / block_size < 3*/)
		return it_array;

	s_FJBlockInfo<Iterator> info =
	    build_fj_block_info(it_array, block_size, size);

	if (info.main == 0)
		return it_array;

	// 1. Construir secuencia Jacobsthal SOBRE BLOQUES
	s_JacobsthalSeq js = buildJacobstahlSeq(info.pend_blocks);
	std::size_t start;
	std::size_t target_main_pos = info.pend_blocks;
	for (size_t i = 0; i < js.size; i++)
	{
		start = js.seq[i] - 1;
		std::size_t end = i > 0 ? js.seq[i - 1] : 0;
		for (size_t j = start + 1; j-- > end;)
		{
			int key = *info.pend[j * block_size + (block_size - 1)];
			target_main_pos = binary_search_block_pos(key, info, 0, j + 2);
			std::size_t from_index = target_main_pos * block_size;
			std::size_t count =
			    info.main_size - from_index; // elementos a desplazar
			shift_right(info.main, from_index, count, block_size);

			// Insertion
			for (size_t k = 0; k < block_size; k++)
				info.main[target_main_pos * block_size + k] =
				    info.pend[j * block_size + k];
			info.main_size += block_size;
			++info.main_blocks;
			++info.inserted_blocks;
		}
	}
	if (info.inserted_blocks < info.pend_blocks)
	{
		size_t remaining = info.pend_blocks - info.inserted_blocks;

		for (size_t j = start + remaining; j-- > start;)
		{
			int key = *info.pend[j * block_size + (block_size - 1)];
			target_main_pos = binary_search_block_pos(key, info, 0, j + 2);
			std::size_t from_index = target_main_pos * block_size;
			std::size_t count =
			    info.main_size - from_index; // elementos a desplazar
			shift_right(info.main, from_index, count, block_size);

			// Insertion
			for (size_t k = 0; k < block_size; k++)
				info.main[target_main_pos * block_size + k] =
				    info.pend[j * block_size + k];
			info.main_size += block_size;
			++info.main_blocks;
			++info.inserted_blocks;
		}
	}

	// Checks if there are leftovers inside the pend
	std::size_t leftover = info.pend_size - info.pend_blocks * block_size;

	if (leftover > 0)
	{
		// Adds the leftover at the end of main
		for (std::size_t j = 0; j < leftover; j++)
			info.main[info.main_size + j] =
			    info.pend[info.pend_blocks * block_size + j];

		info.main_size += leftover;
	}

	delete[] info.pend;
	Iterator *result = ford_johson_insertion(info.main, block_size / 2, size);
	delete[] it_array;
	return result;
}

template <typename Iterator>
Iterator *ford_johnson_pairs(Iterator *it_array, std::size_t block_size,
                             size_t size)
{
	if (block_size == 0 || block_size >= size)
		return it_array;

	std::size_t double_block_size = block_size * 2;

	for (size_t i = 0; i + double_block_size <= size; i += double_block_size)
	{
		if (*it_array[i + block_size - 1] >
		    *it_array[i + double_block_size - 1])
			swap_blocks(it_array, block_size, i);
	}

	return ford_johnson_pairs(it_array, double_block_size, size);
}

template <typename Container>
typename Container::iterator *ford_johnson(Container &cont)
{
	typedef typename Container::iterator iterator;
	std::size_t size = cont.size();

	iterator *it_array =
	    ford_johnson_pairs(get_iterator_array(cont, size), 1, size);
	std::size_t block = 1;
	while (block * 2 <= size)
		block *= 2;

	block /= 2; // primer nivel de inserción

	it_array = ford_johson_insertion(it_array, block, size);

	return it_array;
}
