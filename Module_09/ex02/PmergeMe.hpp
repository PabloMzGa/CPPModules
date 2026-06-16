/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:25:21 by pablo             #+#    #+#             */
/*   Updated: 2026/06/17 01:01:11 by pablo            ###   ########.fr       */
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
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <cassert>
#include <iostream>
#include <sstream>

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
	template <typename Container> void print_container(const Container &cont);

	std::vector<unsigned int> _vector;
	std::deque<unsigned int> _deque;
	std::list<unsigned int> _list;

	double _vector_time_ms;
	double _deque_time_ms;
	double _list_time_ms;
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
void PmergeMe::print_container(const Container &cont)
{
	bool first = true;
	for (typename Container::const_iterator it = cont.begin(); it != cont.end();
	     ++it)
	{
		if (!first)
			std::cout << ' ';
		std::cout << *it;
		first = false;
	}
	std::cout << std::endl;
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

namespace ford_johson
{

/**
 * @brief Describes a single block used during the Ford–Johnson algorithm.
 *
 * Each block represents a contiguous group of iterators of size `block_size`.
 * MAIN and PEND blocks share this structure, but only PEND blocks require
 * pairing information and insertion tracking.
 *
 * @tparam Iterator Iterator type stored inside the block.
 *
 * @param block_start Pointer to the first iterator belonging to this block.
 * @param pair        Pointer to the corresponding MAIN block (only meaningful
 *                    for PEND blocks). Set to NULL if no partner exists.
 * @param block_index Logical index of the block within MAIN or PEND.
 * @param block_value Key value used for comparisons (typically the last element
 *                    of the block).
 * @param inserted    Marks whether this PEND block has already been inserted
 *                    into the MAIN sequence.
 */
template <typename Iterator> struct s_Block
{
	Iterator *block_start;
	s_Block *pair;
	std::size_t block_index;
	unsigned int block_value;
	bool inserted;
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
 * @brief Holds the MAIN and PEND block groups used during the
 *        Ford–Johnson insertion phase.
 *
 * This structure simply groups the two block sequences produced by
 * the block‑building stage: the MAIN chain (already ordered blocks)
 * and the PEND chain (blocks that must be inserted later).
 *
 * @tparam Iterator Iterator type stored inside each block.
 *
 * @param main       Pointer to the array of MAIN blocks.
 * @param main_size  Number of MAIN blocks.
 * @param pend       Pointer to the array of PEND blocks.
 * @param pend_size  Number of PEND blocks.
 */
template <typename Iterator> struct s_SequenceContainer
{
	s_Block<Iterator> *main;
	std::size_t main_size;
	s_Block<Iterator> *pend;
	std::size_t pend_size;
};

/**
 * @brief Aggregates all working data required during one level of the
 *        Ford–Johnson insertion phase.
 *
 * @tparam Iterator Iterator type used by the input container.
 *
 * @param it_array        Pointer to the iterator array representing the
 *                        current sequence at this recursion level.
 * @param size            Total number of elements in the sequence.
 * @param block_size      Size of each block at the current stage of the
 *                        algorithm.
 * @param container       Structure holding the MAIN and PEND block groups.
 * @param buffer          Working buffer where blocks are shifted and inserted.
 *                        Becomes the next iterator array for the next
 *                        recursion.
 * @param inserted_blocks Number of blocks already placed in the buffer
 *                        (initial MAIN blocks + inserted PEND blocks).
 * @param js              Precomputed Jacobsthal sequence used to determine
 *                        the insertion order of PEND blocks.
 */
template <typename Iterator> struct FJState
{
	Iterator *it_array;
	std::size_t size;
	std::size_t block_size;

	s_SequenceContainer<Iterator> container;
	Iterator *buffer;
	std::size_t inserted_blocks;

	s_JacobsthalSeq js;
};

/**
 * @brief Builds the MAIN and PEND block sequences for the Ford–Johnson
 * algorithm.
 *
 * This function partitions the iterator array into fixed-size blocks and
 * assigns each block to either the MAIN or PEND sequence:
 *
 *   - MAIN receives block 0 and all odd-indexed blocks.
 *
 *   - PEND receives all even-indexed blocks except block 0.
 *
 * Each block is initialized with its starting iterator, its comparison key
 * (the last element of the block), and metadata required for later insertion.
 * PEND blocks are immediately paired with their corresponding MAIN blocks
 * (MAIN[2 + p]) during construction, eliminating the need for a separate
 * pairing pass.
 *
 * @tparam Iterator Iterator type used by the input container.
 *
 * @param it_array    Pointer to the array of iterators representing the input.
 * @param size        Total number of elements in the sequence.
 * @param block_size  Size of each block to construct.
 *
 * @return A s_SequenceContainer containing the MAIN and PEND block groups.
 */
template <typename Iterator>
s_SequenceContainer<Iterator>
build_sequences(Iterator *it_array, std::size_t size, std::size_t block_size)
{
	s_SequenceContainer<Iterator> container;

	std::size_t total_blocks = size / block_size;
	if (block_size == 0 || total_blocks == 0)
	{
		container.main = NULL;
		container.main_size = 0;
		container.pend = NULL;
		container.pend_size = 0;
		return container;
	}

	std::size_t main_blocks = 1 + total_blocks / 2;
	std::size_t pend_blocks = (total_blocks > 1 ? (total_blocks - 1) / 2 : 0);

	container.main = new s_Block<Iterator>[main_blocks];
	container.main_size = main_blocks;

	container.pend = new s_Block<Iterator>[pend_blocks];
	container.pend_size = pend_blocks;

	std::size_t main_i = 0;
	std::size_t pend_i = 0;

	for (std::size_t block = 0; block < total_blocks; ++block)
	{
		Iterator *block_start = &it_array[block * block_size];

		s_Block<Iterator> info;
		info.block_start = block_start;
		info.pair = NULL;
		info.inserted = false;

		info.block_value =
		    static_cast<unsigned int>(*block_start[block_size - 1]);

		if (block == 0 || (block % 2 == 1))
		{
			info.block_index = main_i;
			container.main[main_i++] = info;
		}
		else
		{
			info.block_index = pend_i;
			container.pend[pend_i] = info;
			std::size_t main_idx = 2 + pend_i;
			if (main_idx < main_blocks)
				container.pend[pend_i].pair = &container.main[main_idx];
			else
				container.pend[pend_i].pair = NULL;
			++pend_i;
		}
	}
	return container;
}

/**
 * @brief Builds the insertion buffer used during the Ford–Johnson merge phase.
 *
 * The buffer is constructed in three consecutive regions:
 *
 *   1. MAIN blocks are copied first, preserving their internal order.
 *
 *   2. A hole is reserved for all PEND blocks (space only, no writes).
 *
 *   3. Any leftover elements (size % block_size) are copied at the end.
 *
 * The resulting buffer layout is:
 *
 *     [ MAIN blocks ][   hole for PEND   ][ leftover elements ]
 *
 * This buffer becomes the working array for the next recursion level, where
 * PEND blocks will be inserted into and current blocks will be shifted right
 * into the hole.
 *
 * @tparam Iterator Iterator type used by the input container.
 *
 * @param it_array    Pointer to the original iterator array.
 * @param container   Structure containing MAIN and PEND block descriptors.
 * @param size        Total number of elements in the sequence.
 * @param block_size  Size of each block in MAIN and PEND.
 *
 * @return A newly allocated array containing the arranged insertion buffer.
 */
template <typename Iterator>
Iterator *build_insertion_buffer(Iterator *it_array,
                                 const s_SequenceContainer<Iterator> &container,
                                 std::size_t size, std::size_t block_size)
{
	Iterator *buffer = new Iterator[size];
	std::size_t pos = 0;

	for (std::size_t b = 0; b < container.main_size; ++b)
	{
		Iterator *block_start = container.main[b].block_start;
		for (std::size_t k = 0; k < block_size; ++k)
			buffer[pos++] = block_start[k];
	}
	std::size_t hole = container.pend_size * block_size;
	pos += hole;
	std::size_t leftover = size % block_size;

	if (leftover > 0)
	{
		std::size_t start = size - leftover;
		for (std::size_t i = start; i < size; ++i)
			buffer[pos++] = it_array[i];
	}
	return buffer;
}

/**
 * @brief Performs a binary search over block boundaries to find the insertion
 *        position for a PEND block.
 *
 * The search operates on blocks of fixed size, comparing each block by the
 * value of its last element. It returns the block index where the PEND block
 * should be inserted to preserve global order.
 *
 * The search range is [start_block, end_block), meaning that `end_block` is an
 * EXCLUSIVE upper bound. In the Ford–Johnson algorithm, values such as
 * `pair->block_index` or `inserted_blocks` are already exclusive limits, so
 * they can be passed directly as `end_block`.
 *
 * @param value        Comparison key of the PEND block.
 * @param buffer       Array containing the MAIN blocks.
 * @param start_block  First block index to include (inclusive).
 * @param end_block    Upper bound of the search (exclusive).
 * @param block_size   Number of elements per block.
 *
 * @return The block index where the block should be inserted.
 */

template <typename Iterator>
std::size_t binary_search_block_pos(unsigned int value, Iterator *buffer,
                                    std::size_t start_block,
                                    std::size_t end_block,
                                    std::size_t block_size)
{
	if (block_size == 0)
		return 0;

	if (start_block > end_block)
		return start_block;

	std::size_t left = start_block;
	std::size_t right = end_block;

	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;
		std::size_t last_index = (mid + 1) * block_size - 1;
		unsigned int mid_value = *buffer[last_index];

		if (value <= mid_value)
			right = mid;
		else
			left = mid + 1;
	}

	return left;
}

/**
 * @brief Shifts a contiguous range of elements to the right.
 *
 * Moves `count` elements starting at `from_index` exactly `shift` positions
 * to the right inside an array of size `total_size`. Copying is performed
 * right‑to‑left to avoid overwriting source data. Aborts if the shifted range
 * would exceed array bounds.
 *
 * @tparam Iterator  Element or iterator type stored in the array.
 *
 * @param arr         Target array.
 * @param from_index  First element to shift.
 * @param count       Number of elements to move.
 * @param shift       Number of positions to shift right.
 * @param total_size  Total size of the array.
 */
template <typename Iterator>
void shift_right(Iterator *arr, std::size_t from_index, std::size_t count,
                 std::size_t shift, std::size_t total_size)
{
	if (count == 0 || shift == 0)
		return;
	if (from_index + count - 1 + shift >= total_size)
	{
		std::cerr << "FATAL: shift_right out of bounds from_index="
		          << from_index << " count=" << count << " shift=" << shift
		          << " last_dest_index=" << (from_index + count - 1 + shift)
		          << " total_size=" << total_size << "\n";
		abort();
	}
	for (std::size_t i = count; i > 0; --i)
		arr[from_index + i - 1 + shift] = arr[from_index + i - 1];
}

/**
 * @brief Inserts a PEND block into the MAIN buffer while preserving order.
 *
 * Locates the correct insertion position using a binary search bounded by the
 * block's MAIN partner, shifts existing blocks to open space, updates the
 * logical indices of affected MAIN blocks, and marks the PEND block as
 * inserted.
 *
 * The binary search is performed over the block range [0, upper), where
 * `upper` is an EXCLUSIVE limit. In the Ford–Johnson algorithm, both
 * `pair->block_index` and `inserted_blocks` naturally act as exclusive
 * boundaries, so they can be passed directly to the search.
 *
 * @tparam Iterator  Iterator type stored in the blocks.
 * @param st         Insertion‑phase state (buffer, MAIN/PEND sequences,
 *                   counters).
 * @param pend_block_index  Index of the PEND block to insert.
 *
 * @note Calls with out‑of‑range indices, already‑inserted blocks, or when no
 *       complete blocks remain are ignored safely.
 */

template <typename Iterator>
void insert_block_into_main(FJState<Iterator> &st, std::size_t pend_block_index)
{
	// Safety Checks
	if (pend_block_index >= st.container.pend_size)
		return;

	s_Block<Iterator> &small = st.container.pend[pend_block_index];

	if (small.inserted)
		return;

	std::size_t total_blocks = st.size / st.block_size;
	if (st.inserted_blocks >= total_blocks)
		return;

	// Aliases
	s_SequenceContainer<Iterator> &container = st.container;
	Iterator *buffer = st.buffer;
	std::size_t block_size = st.block_size;
	Iterator *block_start = small.block_start;
	unsigned int key = small.block_value;

	// Fallback for pend blocks without pair.
	std::size_t upper = st.inserted_blocks;
	if (small.pair)
		upper = std::min(small.pair->block_index, st.inserted_blocks);

	std::size_t target_pos =
	    (upper == 0)
	        ? 0
	        : binary_search_block_pos(key, buffer, 0, upper, block_size);

	std::size_t from_index = target_pos * block_size;
	std::size_t count = st.inserted_blocks * block_size - from_index;
	shift_right(buffer, from_index, count, block_size, st.size);

	std::size_t base = target_pos * block_size;
	for (std::size_t k = 0; k < block_size; ++k)
		buffer[base + k] = block_start[k];

	// Optimized loop for minimum comparisons.
	for (std::size_t i = 0; i < container.main_size; ++i)
	{
		if (container.main[i].block_index < target_pos)
			continue;

		for (; i < container.main_size; ++i)
			container.main[i].block_index++;

		break;
	}
	st.inserted_blocks++;
	small.inserted = true;
}

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
s_JacobsthalSeq build_jacobsthal_seq(std::size_t size);

/**
 * @brief Inserts PEND blocks according to the Jacobsthal schedule.
 *
 * For each Jacobsthal limit, inserts only the new PEND blocks in the
 * range (last .. limit‑1), in descending order. This prevents duplicate
 * insertions and preserves the staged Ford–Johnson insertion pattern.
 *
 * @tparam Iterator  Iterator type stored in the blocks.
 * @param fj_state   Current insertion‑phase state.
 */
template <typename Iterator>
void process_jacobsthal_blocks(FJState<Iterator> &fj_state)
{
	s_SequenceContainer<Iterator> &container = fj_state.container;
	const s_JacobsthalSeq &js = fj_state.js;

	if (container.pend_size == 0)
		return;

	std::size_t last = 0;

	for (std::size_t i = 0; i < js.size; ++i)
	{
		std::size_t jacobsthal_limit = fj_state.js.seq[i];
		for (std::size_t j = jacobsthal_limit; j-- > last;)
			insert_block_into_main(fj_state, j);

		last = jacobsthal_limit;
	}
}

/**
 * @brief Inserts all remaining PEND blocks after the Jacobsthal phase.
 *
 * Determines how many PEND blocks have already been inserted and then
 * inserts the rest in ascending order. This completes the insertion phase
 * once the Jacobsthal schedule has finished.
 *
 * @tparam Iterator   Iterator type stored in the blocks.
 * @param fj_state    Current insertion-phase state.
 */
template <typename Iterator>
void process_remaining_blocks(FJState<Iterator> &fj_state)
{
	s_SequenceContainer<Iterator> &container = fj_state.container;

	if (container.pend_size == 0)
		return;
	std::size_t inserted_pend =
	    fj_state.inserted_blocks - fj_state.container.main_size;

	if (inserted_pend >= container.pend_size)
		return;

	for (std::size_t i = inserted_pend; i < container.pend_size; ++i)
		insert_block_into_main(fj_state, i);
}

/**
 * @brief Initializes the Ford–Johnson insertion state.
 *
 * Builds the MAIN and PEND block sequences, allocates the initial insertion
 * buffer containing all MAIN blocks, initializes the insertion counters, and
 * generates the Jacobsthal sequence required for the PEND‑insertion phase.
 *
 * If no complete MAIN blocks exist, the state is returned in an empty and
 * inert form (no buffer, no Jacobsthal sequence, and zero inserted blocks).
 *
 * @tparam Iterator  Iterator type used to access the input array.
 *
 * @param it_array     Pointer to the array of iterators representing the input.
 * @param size         Total number of elements in the input.
 * @param block_size   Number of elements per block.
 *
 * @return A fully initialized FJState ready for the insertion phase, or an
 *         empty state if no MAIN blocks can be formed.
 */
template <typename Iterator>
FJState<Iterator> init_fj_state(Iterator *it_array, std::size_t size,
                                std::size_t block_size)
{
	FJState<Iterator> st;

	st.it_array = it_array;
	st.size = size;
	st.block_size = block_size;
	st.container = build_sequences(it_array, size, block_size);

	if (st.container.main_size == 0)
	{
		st.buffer = NULL;
		st.inserted_blocks = 0;
		st.js.size = 0;
		return st;
	}

	st.buffer =
	    build_insertion_buffer(it_array, st.container, size, block_size);
	st.inserted_blocks = st.container.main_size;
	st.js = build_jacobsthal_seq(st.container.pend_size);
	return st;
}

/**
 * @brief Executes one Ford–Johnson insertion phase.
 *
 * Builds MAIN/PEND blocks, inserts all PEND blocks (first via Jacobsthal,
 * then sequentially), and recurses with half the block size until no further
 * subdivision is possible. Each call takes ownership of the input buffer and
 * frees it before returning.
 *
 * Base cases:
 *   - `block_size == 0` or `block_size >= size`
 *   - No MAIN blocks can be formed
 *
 * @tparam Iterator  Iterator type.
 * @param it_array   Input buffer (ownership transferred).
 * @param block_size Current block size.
 * @param size       Total number of elements.
 *
 * @return Pointer to the buffer produced by the deepest recursive step.
 */
template <typename Iterator>
Iterator *ford_johson_insertion(Iterator *it_array, std::size_t block_size,
                                std::size_t size)
{
	if (block_size == 0 || block_size >= size)
		return it_array;
	FJState<Iterator> fj_state = init_fj_state(it_array, size, block_size);

	if (fj_state.container.main_size == 0)
		return it_array;

	process_jacobsthal_blocks(fj_state);
	process_remaining_blocks(fj_state);
	Iterator *result =
	    ford_johson_insertion(fj_state.buffer, block_size / 2, size);
	delete[] fj_state.container.main;
	delete[] fj_state.container.pend;
	delete[] it_array;
	return result;
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
