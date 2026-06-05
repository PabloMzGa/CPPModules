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

struct JacobsthalSeq
{
	std::size_t seq[64]; // array dinámico con J_k
	std::size_t size;	 // cuántos valores contiene
};

// Jn = (2^n+1 + (-1)^n) / 3
JacobsthalSeq buildJacobstahlSeq(std::size_t pend_size)
{
	std::size_t jn;
	JacobsthalSeq js;
	js.size = 0;
	for (size_t n = 2; n < 64; n++)
	{
		jn = ((1LL << (n + 1)) + (n % 2 == 0 ? 1 : -1)) / 3;

		// std::cout << "jn = " << jn << " pend_size " << pend_size << std::endl;
		if (jn > pend_size + 1)
			break;
		js.seq[js.size++] = jn - 1; // Make sequence 0 based
	}
	return js;
}

template <typename Iterator>
struct FJBlockInfo
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

template <typename Iterator>
void swap_pairs(Iterator *it_array, std::size_t pair_size, std::size_t pos)
{
	for (std::size_t i = pos; i < pos + pair_size; ++i)
		std::swap(it_array[i], it_array[i + pair_size]);
}

template <typename Iterator>
void shift_right(Iterator *arr, std::size_t from_index, std::size_t count,
				 std::size_t shift)
{
	if (count == 0 || shift == 0)
		return;
	for (std::size_t i = count; i > 0; --i)
		arr[from_index + i - 1 + shift] = arr[from_index + i - 1];
}

// template <typename Iterator>
// std::size_t binary_search_block_pos(int value,
// 									const FJBlockInfo<Iterator> &info)
// {
// 	if (info.block_size == 0 || info.main_blocks == 0)
// 		return 0;

// 	std::size_t left = 0;
// 	std::size_t right = info.main_blocks;

// 	while (left < right)
// 	{
// 		std::size_t mid = left + (right - left) / 2;
// 		std::size_t last_index = (mid + 1) * info.block_size - 1;

// 		// 🔴 IMPORTANTE: no salirte de main_size
// 		if (last_index >= info.main_size)
// 			last_index = info.main_size - 1;
// 		if (value <= *info.main[last_index])
// 			right = mid;
// 		else
// 			left = mid + 1;
// 	}

// 	return left;
// }

template <typename Iterator>
std::size_t binary_search_block_pos(int value,
									const FJBlockInfo<Iterator> &info,
									std::size_t start_block,
									std::size_t end_block)
{
	// Guardas rápidas
	if (info.block_size == 0 || info.main_blocks == 0)
		return 0;

	// Clamp de los límites al rango válido [0, info.main_blocks-1]
	if (start_block >= info.main_blocks)
		return info.main_blocks; // insertar al final
	if (end_block >= info.main_blocks)
		end_block = info.main_blocks - 1;
	if (start_block > end_block)
		return start_block; // intervalo vacío -> insertar en start_block

	// right es exclusive: queremos buscar en [left, right)
	std::size_t left = start_block;
	std::size_t right = end_block + 1;

	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;

		// índice del último elemento del bloque mid
		std::size_t last_index = (mid + 1) * info.block_size;
		if (last_index == 0)
			last_index = 0;
		else
			last_index = last_index - 1;

		// No salirnos de main_size
		if (last_index >= info.main_size)
			last_index = (info.main_size == 0) ? 0 : info.main_size - 1;

		if (value <= *info.main[last_index])
			right = mid;
		else
			left = mid + 1;
	}

	return left;
}

template <typename Iterator>
FJBlockInfo<Iterator> build_fj_block_info(Iterator *it_array,
										  std::size_t block_size, size_t size)
{

	FJBlockInfo<Iterator> info;
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
	/*
	if ((size / block_size) < 3)
	return info;
	*/

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

		// 🔴 Si el bloque es incompleto, NO va a main
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

// TODO: Ordenar, documentar e incluir orden de Jacobstalh

#include <iostream>
#include <cstddef>

// Asume que JacobsthalSeq está definido como en tu código:
// struct JacobsthalSeq { std::size_t seq[64]; std::size_t size; };

void printJacobsthalStruct(const JacobsthalSeq &js, bool one_based = false)
{
	if (js.size == 0)
	{
		std::cout << "JacobsthalSeq: (vacía)\n";
		return;
	}

	std::cout << "JacobsthalSeq size = " << js.size << "  seq (0-based):";
	for (std::size_t i = 0; i < js.size; ++i)
	{
		std::cout << ' ' << js.seq[i];
	}
	std::cout << '\n';

	if (one_based)
	{
		std::cout << "JacobsthalSeq (1-based):";
		for (std::size_t i = 0; i < js.size; ++i)
		{
			std::cout << ' ' << (js.seq[i] + 1);
		}
		std::cout << '\n';
	}
}

template <typename Iterator>
Iterator *ford_johson_insertion(Iterator *it_array, std::size_t block_size,
								size_t size)
{
	std::cout << "Iniciando inserción" << std::endl;

	if (block_size == 0 || block_size >= size /*|| size / block_size < 3*/)
		return it_array;

	FJBlockInfo<Iterator> info =
		build_fj_block_info(it_array, block_size, size);

	if (info.main == 0)
		return it_array;

	std::cout << "Main = ";
	print_iter_array(info.main, info.main_size);
	std::cout << "Pend = ";
	print_iter_array(info.pend, info.pend_size);

	// for (size_t i = 0; i < info.pend_blocks; i++)
	// {
	// 	// Last value of the current pend block
	// 	int key = *info.pend[i * block_size + (block_size - 1)];

	// 	target_main_pos = binary_search_block_pos(key, info);
	// 	shift_right(info.main, target_main_pos * block_size,
	// 				info.main_size - target_main_pos * block_size, block_size);

	// 	// Insertion
	// 	for (size_t j = 0; j < block_size; j++)
	// 		info.main[target_main_pos * block_size + j] =
	// 			info.pend[i * block_size + j];
	// 	info.main_size += block_size;
	// 	++info.main_blocks;
	// }

	// 1. Construir secuencia Jacobsthal SOBRE BLOQUES
	JacobsthalSeq js = buildJacobstahlSeq(info.pend_blocks);
	printJacobsthalStruct(js, 1);
	std::cout << "js.size = " << js.size << std::endl;
	std::size_t start;
	std::size_t target_main_pos = info.pend_blocks;
	for (size_t i = 0; i < js.size; i++)
	{
		start = js.seq[i] - 1;
		std::size_t end = i > 0 ? js.seq[i - 1] : 0;
		std::cout << "start = " << start << " end = " << end << std::endl;
		for (size_t j = start + 1; j-- > end;)
		{
			int key = *info.pend[j * block_size + (block_size - 1)];
			std::cout << "j = " << j << " key = " << key << std::endl;
			target_main_pos = binary_search_block_pos(key, info, 0, j + 2);
			std::cout << "target_main_pos = " << target_main_pos << std::endl;
			std::cout << "Main pre insertion  ";
			print_iter_array(info.main, info.main_size);
			std::size_t from_index = target_main_pos * block_size;
			std::size_t count = info.main_size - from_index; // elementos a desplazar
			shift_right(info.main, from_index, count, block_size);

			// Insertion
			for (size_t k = 0; k < block_size; k++)
				info.main[target_main_pos * block_size + k] =
					info.pend[j * block_size + k];
			info.main_size += block_size;
			++info.main_blocks;
			++info.inserted_blocks;
			std::cout << "Main post insertion ";
			print_iter_array(info.main, info.main_size);
		}
	}
	if (info.inserted_blocks < info.pend_blocks)
	{
		std::cout << " Bloques sobrante, start = " << start << std::endl;
		for (size_t j = info.pend_blocks; j-- > start;)
		{
			if (info.inserted_blocks < info.pend_blocks)
			{

				int key = *info.pend[j * block_size + (block_size - 1)];
				std::cout << "j = " << j << " key = " << key << std::endl;
				target_main_pos = binary_search_block_pos(key, info, 0, j + 2);
				std::cout << "target_main_pos = " << target_main_pos << std::endl;
				std::cout << "Main pre insertion  ";
				print_iter_array(info.main, info.main_size);
				std::size_t from_index = target_main_pos * block_size;
				std::size_t count = info.main_size - from_index; // elementos a desplazar
				shift_right(info.main, from_index, count, block_size);

				// Insertion
				for (size_t k = 0; k < block_size; k++)
					info.main[target_main_pos * block_size + k] =
						info.pend[j * block_size + k];
				info.main_size += block_size;
				++info.main_blocks;
				++info.inserted_blocks;
				std::cout << "Main post insertion ";
				print_iter_array(info.main, info.main_size);
			}
		}
	}

	// Checks if there are leftovers inside the pend
	std::size_t leftover = info.pend_size - info.pend_blocks * block_size;

	if (leftover > 0)
	{
		std::cout << "Añadiendo sobrante" << std::endl;
		// Adds the leftover at the end of main
		for (std::size_t j = 0; j < leftover; j++)
			info.main[info.main_size + j] =
				info.pend[info.pend_blocks * block_size + j];

		info.main_size += leftover;
	}

	delete[] info.pend;
	std::cout << "Main size = " << info.main_size << std::endl;
	std::cout << "Block size = " << block_size << " secuencia -> ";
	print_iter_array(info.main, info.main_size);
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
			swap_pairs(it_array, block_size, i);
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
