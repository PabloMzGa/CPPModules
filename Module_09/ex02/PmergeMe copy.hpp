/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe copy.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:25:21 by pablo             #+#    #+#             */
/*   Updated: 2026/06/15 20:15:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ctime>
#include <deque>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class PmergeMe
{
  public:
	PmergeMe();
	PmergeMe(const PmergeMe &src);
	PmergeMe(const std::string &input);
	PmergeMe &operator=(const PmergeMe &src);
	~PmergeMe();
	void sort();

  private:
	static unsigned int parse_positive_int(const std::string &token);
	template <typename Container> static bool is_sorted(const Container &src);
	template <typename Container>
	static void load_values(const std::string &input, Container &container);
	template <typename Container>
	static void apply_order(Container &cont,
	                        typename Container::iterator *it_array);

	std::vector<unsigned int> _vector;
	std::deque<unsigned int> _deque;

	double _vector_time_ms;
	double _deque_time_ms;
};

template <typename Container>
void PmergeMe::load_values(const std::string &input, Container &container)
{
	unsigned int value;

	std::stringstream ss(input);
	std::string token;
	while (ss >> token)
	{
		value = parse_positive_int(token);
		container.push_back(value);
	}
	if (container.empty())
		throw std::runtime_error("Error: no numbers provided");
}

template <typename Container> bool PmergeMe::is_sorted(const Container &src)
{
	if (src.size() <= 1)
		return (true);
	typename Container::const_iterator it = src.begin();
	typename Container::const_iterator prev = it;
	++it;
	for (; it != src.end(); ++it, ++prev)
	{
		if (*prev > *it)
			return (false);
	}
	return (true);
}

template <typename Container>
void PmergeMe::apply_order(Container &cont,
                           typename Container::iterator *it_array)
{
	Container tmp; // Crea un contenedor temporal vacío

	// Copiamos los valores en el orden indicado por it_array
	std::size_t n = cont.size();
	for (std::size_t i = 0; i < n; ++i)
		tmp.push_back(*it_array[i]);

	// Sustituimos el contenedor original por el ordenado
	cont = tmp;
	delete[] it_array;
}

#include <iostream>
namespace ford_johson
{
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

template <typename Iterator>
struct s_IteratorPair
{
    Iterator it;                 // Iterador real al elemento
    s_IteratorPair* pair;        // Puntero a su pareja (a_i <-> b_i)
    bool is_big;                 // true = bloque grande (b_i), false = pequeño (a_i)
    std::size_t block_index;     // Índice del bloque al que pertenece
};


/**
 * @struct s_JacobsthalSeq
 * An struct containing an array with several Jacobsthal Numbers
 *
 * @param seq A fixed array for containing the numbers. It's size is 64 because
 *            65th Jacobsthal number is bigger than SIZE_MAX in 64 bits.
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
 * @brief Builds and returns a s_JacobsthalSeq.
 *
 * It generates a sequence of Jacobsthal's numbers, a sequence where a number
 * is the sum of the previous and two times the preovious before that. The
 * sequence is returned in a 0 based basis.
 *
 * @param size Number of Jacobsthal numbers required.
 *
 * @return A s_JacobsthalSeq object containing the required sequence.
 */
s_JacobsthalSeq buildJacobsthalSeq(std::size_t size);

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
binary_search_block_pos(unsigned int value, const s_FJBlockInfo<Iterator> &info,
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
		// Safe mid calculation
		std::size_t mid = left + (right - left) / 2;

		// Last index from the mid block
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

/**
 * @brief Inserts a full block from 'pend' into its sorted position in 'main'.
 *
 * Performs a block-level insertion using the Ford–Johnson optimization:
 * the binary search is restricted to the range of blocks where the current
 * block can legally fall. For a pend block at index j, the valid search
 * interval ends at j+1, because block j originates from the pair (j, j+1)
 * and therefore cannot be inserted beyond the position of block j+1.
 *
 * It ensures that the search never exceeds the number of blocks already
 * inserted into 'main' and never explores positions that are impossible
 * according to the Ford–Johnson ordering constraints.
 *
 * After determining the insertion position, the function shifts the
 * necessary blocks to the right and copies the selected block from 'pend'
 * into the resulting gap, updating all size and block counters.
 *
 * @param info              Ford–Johnson block metadata (main/pend arrays and
 * sizes).
 * @param pend_block_index  Index of the block inside 'pend' to be inserted.
 * @param block_size        Size of each block (number of elements per block).
 */
template <typename Iterator>
void insert_block_into_main(s_FJBlockInfo<Iterator> &info,
                            std::size_t pend_block_index,
                            std::size_t block_size)
{
	unsigned int key = *info.pend[pend_block_index * block_size + (block_size - 1)];
	std::size_t upper = pend_block_index + info.inserted_blocks;
	for (size_t i = pend_block_index + 1; i < info.pend_blocks; i++)
	{
		if (key > *info.pend[i * block_size + (block_size - 1)])
			++upper;
	}

	std::size_t target_main_pos = binary_search_block_pos(key, info, 0, upper);

	std::size_t from_index = target_main_pos * block_size;
	std::size_t count = info.main_size - from_index;

	shift_right(info.main, from_index, count, block_size);

	for (std::size_t k = 0; k < block_size; k++)
		info.main[target_main_pos * block_size + k] =
		    info.pend[pend_block_index * block_size + k];

	info.main_size += block_size;
	++info.main_blocks;
	++info.inserted_blocks;
}

/**
 * @brief Inserts blocks from 'pend' into 'main' following the Jacobsthal order.
 *
 * Iterates over the Jacobsthal sequence and inserts the corresponding blocks
 * from 'pend' into 'main' using block-level insertion. The Jacobsthal sequence
 * determines the order in which blocks are inserted to minimize comparisons.
 *
 * @param info        Ford–Johnson block metadata.
 * @param js          Precomputed Jacobsthal sequence for block insertion.
 * @param block_size  Size of each block.
 * @param last_start  Output: last starting index processed, used for remaining
 *                    blocks outside the Jacobsthal sequence.
 */
template <typename Iterator>
void process_jacobsthal_blocks(s_FJBlockInfo<Iterator> &info,
                               const s_JacobsthalSeq &js,
                               std::size_t block_size, std::size_t &last_start)
{
	for (std::size_t i = 0; i < js.size; i++)
	{
		std::size_t start = js.seq[i] - 1;
		std::size_t end = (i > 0 ? js.seq[i - 1] : 0);

		for (std::size_t j = start + 1; j-- > end;)
		{
			insert_block_into_main(info, j, block_size);
			std::cout << "Insertado bloque jacobsthl " << j << std::endl;
			std::cout << "Main = ";
			print_iter_array(info.main, info.main_size);
			std::cout << "Pend = ";
			print_iter_array(info.pend, info.pend_size);
		}

		last_start = start;
	}
}

/**
 * @brief Inserts the remaining blocks not covered by the Jacobsthal sequence.
 *
 * After processing the Jacobsthal-ordered blocks, some blocks may remain
 * uninserted. This function inserts those blocks in descending order, using the
 * same block-level insertion logic as the Jacobsthal phase.
 *
 * @param info        Ford–Johnson block metadata.
 * @param block_size  Size of each block.
 * @param last_start  Last starting index processed during the Jacobsthal phase.
 */
template <typename Iterator>
void process_remaining_blocks(s_FJBlockInfo<Iterator> &info,
                              std::size_t block_size, std::size_t last_start)
{
	if (info.inserted_blocks >= info.pend_blocks)
		return;

	std::size_t remaining = info.pend_blocks - info.inserted_blocks;

	for (std::size_t j = last_start + remaining; j-- > last_start;)
		insert_block_into_main(info, j, block_size);
}

/**
 * @brief Appends leftover elements from 'pend' to the end of 'main'.
 *
 * If the total number of elements in 'pend' is not a multiple of block_size,
 * the final incomplete block is appended directly to the end of 'main' without
 * any binary search or shifting, preserving element order.
 *
 * @param info Ford–Johnson block metadata.
 */
template <typename Iterator> void insert_leftover(s_FJBlockInfo<Iterator> &info)
{
	std::size_t leftover = info.pend_size - info.pend_blocks * info.block_size;

	if (leftover == 0)
		return;

	for (std::size_t j = 0; j < leftover; j++)
		info.main[info.main_size + j] =
		    info.pend[info.pend_blocks * info.block_size + j];

	info.main_size += leftover;
}



/**
 * @brief Performs the Ford–Johnson insertion phase over block-structured data.
 *
 * Recursively applies the Ford–Johnson block insertion strategy:
 *  - Builds block metadata (main/pend distribution).
 *  - Inserts blocks from 'pend' into 'main' using Jacobsthal ordering.
 *  - Inserts remaining blocks not covered by the Jacobsthal sequence.
 *  - Appends leftover elements.
 *  - Recursively repeats the process with half block size.
 *
 * Returns a newly allocated array containing the merged result. The input
 * array is freed inside the function.
 *
 * @param it_array   Input array of iterators.
 * @param block_size Initial block size for the current recursion level.
 * @param size       Total number of elements.
 *
 * @return Pointer to a newly allocated array containing the merged result.
 */
template <typename Iterator>
Iterator *ford_johson_insertion(Iterator *it_array, std::size_t block_size,
                                std::size_t size)
{
	if (block_size == 0 || block_size >= size)
		return it_array;

	s_FJBlockInfo<Iterator> info =
	    build_fj_block_info(it_array, block_size, size);

	std::cout << "Block size = " << block_size << std::endl;
	std::cout << "Main = ";
	print_iter_array(info.main, info.main_size);
	std::cout << "Pend = ";
	print_iter_array(info.pend, info.pend_size);

	if (info.main == 0)
		return it_array;

	s_JacobsthalSeq js = buildJacobsthalSeq(info.pend_blocks);

	std::size_t last_start = 0;

	process_jacobsthal_blocks(info, js, block_size, last_start);
	process_remaining_blocks(info, block_size, last_start);
	insert_leftover(info);
	std::cout << "Main post insertion  ";
	print_iter_array(info.main, info.main_size);

	delete[] info.pend;

	Iterator *result = ford_johson_insertion(info.main, block_size / 2, size);

	delete[] it_array;
	return result;
}

/**
 * @brief Orders adjacent block pairs for the Ford–Johnson algorithm.
 *
 * Compares each pair of consecutive blocks of size `block_size` using their
 * last elements as keys. If the first block is greater, the two blocks are
 * swapped. After processing all pairs, the function recurses with doubled
 * block size.
 *
 * @param it_array   Array of iterators.
 * @param block_size Current block size.
 * @param size       Total number of elements.
 *
 * @return The same pointer `it_array` after pair ordering.
 */
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

/**
 * @brief Runs the full Ford–Johnson sorting procedure on a container.
 *
 * Converts the container into an iterator array, performs the pairing phase
 * starting with block size 1, determines the largest power-of-two block size
 * for insertion, and executes the Ford–Johnson insertion phase. Returns the
 * final sorted iterator array.
 *
 * @param cont Input container.
 * @return Pointer to the sorted iterator array.
 */
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

	block /= 2; // First level

	it_array = ford_johson_insertion(it_array, block, size);

	return it_array;
}
} // namespace ford_johson

#endif
